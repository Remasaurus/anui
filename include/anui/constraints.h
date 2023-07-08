#pragma once
#include "anui/impl/types.h"
#include "anui/utils/concepts.h"
#include "anui/styles.h"
#include <algorithm>
#include <anui/core.h>
#include <functional>

ANUI_BEGIN

namespace constraints
{

    class position_constraint
    {
    public:
        virtual anui::impl::small_number_t x() = 0;
        virtual anui::impl::small_number_t y() = 0;
    };

    class size_constraint
    {
    public:
        virtual anui::impl::small_number_t width() = 0;
        virtual anui::impl::small_number_t height() = 0;
    };

    class any_constraint : public position_constraint, public size_constraint
    {
    };

    namespace ops
    {
        template <typename T, typename U>
        struct plus
        {
            auto operator()(const T &lhs, const U &rhs) { return lhs + rhs; }
        };

        template <typename T, typename U>
        struct min
        {
            auto operator()(const T &lhs, const U &rhs) { return lhs - rhs; }
        };
    }

    template <typename Op, typename T, typename U>
    class constraint_expression : public any_constraint
    {
    public:
        constraint_expression(const T &lhs, const T &rhs) : lhs(lhs), rhs(rhs) {}
        virtual anui::impl::small_number_t x() { return Op{}(lhs, rhs); }
        virtual anui::impl::small_number_t y() { return Op{}(lhs, rhs); }
        virtual anui::impl::small_number_t width() { return Op{}(lhs, rhs); }
        virtual anui::impl::small_number_t height() { return Op{}(lhs, rhs); }

    private:
        const T &lhs;
        const U &rhs;
    };

#define ADD_ARITHMETIC(member)                                        \
    template <typename T>                                             \
    auto operator+(T &&rhs)                                           \
    {                                                                 \
        return constraint_expression<ops::plus<decltype(*this), T>,   \
                                     decltype(*this), T>(*this, rhs); \
    }                                                                 \
                                                                      \
    template <typename T>                                             \
    auto operator-(T &&rhs)                                           \
    {                                                                 \
        return constraint_expression<ops::min<decltype(*this), T>,    \
                                     decltype(*this), T>(*this, rhs); \
    }                                                                 \
                                                                      \
    auto operator-()                                                  \
    {                                                                 \
        member = -member;                                             \
        return *this;                                                 \
    }

    //auto operator+(const decltype(*this)& rhs) \
    //{ member += rhs.#member; return *this; }
    //auto operator- (const decltype(*this)& rhs) \
    //{ member -= rhs.#member; return *this; }

    class PixelConstraint : public interface_constraint
    {
    private:
        anui::impl::small_number_t mPixels;

    public:
        virtual anui::impl::small_number_t x() { return mPixels; }
        virtual anui::impl::small_number_t y() { return mPixels; }
        virtual anui::impl::small_number_t width() { return mPixels; }
        virtual anui::impl::small_number_t height() { return mPixels; }

        ADD_ARITHMETIC(mPixels)
    };

    class PercentageConstraint
    {
    };

    namespace literals
    {

    } // literals

} // constraints

class constraint : public utils::base_container<constraints::interface_constraint>
{
};

ANUI_END
