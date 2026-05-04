#pragma once

#include <concepts>
#include <limits>

namespace scion {
    /// \brief Checks whether integral multiplication would overflow.
    /// \tparam T
    /// \param lhs Left operand.
    /// \param rhs Right operand.
    /// \return Whether integral multiplication would overflow.
    /// \note Reminder that unsigned integral overflow is well-defined (wraps) while signed integral overflow is undefined behaviour.
    template <std::integral T>
    [[nodiscard]] constexpr auto mul_would_overflow(T const lhs, T const rhs) -> bool {
        using limits = std::numeric_limits<T>;

        if constexpr (std::unsigned_integral<T>) {
            return rhs != 0 && lhs > limits::max() / rhs;
        } else {
            if (lhs == 0 || rhs == 0) return false;

            if (lhs > 0) return rhs > 0 ? lhs > limits::max() / rhs : rhs < limits::min() / lhs;

            return rhs > 0 ? lhs < limits::min() / rhs : lhs < limits::max() / rhs;
        }
    }
}
