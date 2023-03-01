#pragma once
#include <vector>
#include <anui/core.h>


ANUI_BEGIN

class WindowBase;


namespace constraints {


enum class Calc {
	X, Y, Width, Height
};

// Interface for WindowClass
class IConstraint {
public:
	virtual unsigned long long toPixel(const WindowBase*, Calc) = 0;
};

// Add and subtract constrains
namespace operations {
	template<typename T>
	concept OperatorConstraintConcept = requires() {
		{ T::op(500, 500) } -> std::same_as<unsigned long long>;
	};

	struct Add {
		static unsigned long long op(unsigned long long lhs, unsigned long long rhs) {
			return lhs + rhs;
		}
	};

	struct Sub {
		static unsigned long long op(unsigned long long lhs, unsigned long long rhs) {
			return lhs - rhs;
		}
	};

} // operations


template<operations::OperatorConstraintConcept Operator,
	typename LHS, typename RHS>
class OperateConstraint : public IConstraint {
public:
	OperateConstraint(const LHS& lhs, const RHS& rhs) : m_Lhs(lhs), m_Rhs(rhs) {}

	unsigned long long toPixel(const WindowBase* ptr, Calc calc) {
		return Operator::op(m_Lhs.toPixel(ptr, calc), m_Rhs.toPixel(ptr, calc));
	}

	template<typename Self, typename RHS>
	OperateConstraint<operations::Add, Self, RHS> operator+ (this Self&& self, RHS&& rhs) {
		return OperateConstraint<operations::Add, Self, RHS>(self, rhs);
	}

	template<typename Self, typename RHS>
	OperateConstraint<operations::Sub, Self, RHS> operator- (this Self&& self, RHS&& rhs) {
		return OperateConstraint<operations::Sub, Self, RHS>(self, rhs);
	}

private:
	LHS m_Lhs;
	RHS m_Rhs;
};

// All constraints must support operator+ and operator-
class Constraint : public IConstraint {
public:
	template<typename Self, typename RHS>
	OperateConstraint<operations::Add, Self, RHS> operator+ (this Self&& self, RHS&& rhs) {
		return OperateConstraint<operations::Add, Self, RHS>(self, rhs);
	}

	template<typename Self, typename RHS>
	OperateConstraint<operations::Sub, Self, RHS> operator- (this Self&& self, RHS&& rhs) {
		return OperateConstraint<operations::Sub, Self, RHS>(self, rhs);
	}
};



class PixelContraint : public Constraint {
public:
	PixelContraint(unsigned long long pixels) : m_Pixels(pixels) {}
	unsigned long long toPixel(const WindowBase*, Calc) override { return m_Pixels; }
private:
	unsigned long long m_Pixels;
};

class PercentConstraint : public Constraint {
public:
	PercentConstraint(long double percentage) : m_Percentage(percentage) {}
	unsigned long long toPixel(const WindowBase*, Calc) override { return m_Percentage; }
private:
	long double m_Percentage;
};

class RemConstraint : public Constraint {
public:
	RemConstraint(long double rem) : m_Rem(rem) {}
	unsigned long long toPixel(const WindowBase*, Calc) override { return m_Rem; }
private:
	long double m_Rem;
};

class CentreConstraint : public Constraint {

};

class AspectConstraint : public Constraint {

};


namespace literals {


	inline PixelContraint operator""_px(unsigned long long x) {
		return PixelContraint(x);
	}

	inline PercentConstraint operator""_pct (long double p) {
		return PercentConstraint(p);
	}
	inline PercentConstraint operator""_pct(unsigned long long p) {
		return PercentConstraint(p);
	}

	inline RemConstraint operator""_rem(long double r) {
		return RemConstraint(r);
	}
	inline RemConstraint operator""_rem(unsigned long long r) {
		return RemConstraint(r);
	}

} // literals
} // constraints

using namespace anui::constraints::literals;

inline constraints::PixelContraint pixel(unsigned long long x) {
	return constraints::PixelContraint(x);
}

inline constraints::PercentConstraint rem(long double r) {
	return constraints::PercentConstraint(r);
}

inline constraints::PercentConstraint percent(long double p) {
	return constraints::PercentConstraint(p);
}

inline constraints::PercentConstraint right() {
	return constraints::PercentConstraint(100);
}


ANUI_END