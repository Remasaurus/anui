#pragma once
#include <cstddef>

namespace anui {

	//
	// Classes
	//
	class size_unit;
	class pos_unit;
	class any_unit;

	// 
	// Units
	// 
	class px;
	class pct;
	class rem;



	//
	// Implementations
	//

	class size_unit {
		virtual std::size_t width() = 0;
		virtual std::size_t height() = 0;
	};

	class pos_unit {
		virtual std::size_t x() = 0;
		virtual std::size_t y() = 0;
	};


	class px : public size_unit, public pos_unit {
	public:
		constexpr px(unsigned long long pixels)
			: pixels(pixels) {}

		operator std::size_t() {
			return pixels;
		}
		
	private:
		std::size_t x();
		std::size_t y();
		std::size_t width();
		std::size_t height();

		unsigned long long pixels;
	};



	class pct : public size_unit, public pos_unit {
	public:
		constexpr pct(long double percentage)
			: percentage(percentage) {}

	private:
		std::size_t x();
		std::size_t y();
		std::size_t width();
		std::size_t height();

		long double percentage;
	};


	class rem : public size_unit, public pos_unit {
	public:
		constexpr rem(long double rems)
			: rems(rems) {}

	private:
		std::size_t x();
		std::size_t y();
		std::size_t width();
		std::size_t height();

		long double rems;
	};



	
	class center;

	class aspect;
	class min;
	class max;
	class between;







	namespace unit_literals {
		constexpr px operator ""_px(unsigned long long pixels) {
			return px(pixels);
		}

		constexpr pct operator ""_pct(long double percentage) {
			return pct(percentage);
		}

		constexpr pct operator ""_pct(unsigned long long percentage) {
			return pct(percentage);
		}


	} // namespace unit_literals
	
} // namespace anui
