#pragma once

#include "scion/core/types.hpp"
#include "scion/core/traits.hpp"
#include "scion/core/arithmetic.hpp"

/// \file scion/core/core.hpp
/// \brief Main file of the core module.

static_assert(scion::mul_would_overflow<scion::u8>(23, 27));
static_assert(!scion::mul_would_overflow<scion::u16>(23, 27));

static_assert(!scion::mul_would_overflow<scion::isize>(std::numeric_limits<scion::isize>::min(), 1));
static_assert(!scion::mul_would_overflow<scion::isize>(std::numeric_limits<scion::isize>::max(), 1));

static_assert(scion::mul_would_overflow<scion::isize>(std::numeric_limits<scion::isize>::max(), 2));
static_assert(scion::mul_would_overflow<scion::isize>(std::numeric_limits<scion::isize>::min(), -1));

namespace scion {
    /// \brief Checks whether integral conversion is safe.
    /// \tparam Src Source type.
    /// \tparam Dst Destination type.
    /// \param val Value to check.
    /// \return Whether integral conversion is safe.
    template <std::integral Src, std::integral Dst>
    [[nodiscard]] constexpr auto safe_integral_conversion(Src const val) noexcept -> bool {
        if constexpr (scion::lossless_integral_conversion_v<Src, Dst>) {
            return true;
        } else if constexpr (std::signed_integral<Src> && std::signed_integral<Dst>) {
            return val >= static_cast<Src>(std::numeric_limits<Dst>::lowest()) && val <= static_cast<Src>(std::numeric_limits<Dst>::max());
        } else if constexpr (std::unsigned_integral<Src> && std::unsigned_integral<Dst>) {
            return val <= static_cast<Src>(std::numeric_limits<Dst>::max());
        } else if constexpr (std::signed_integral<Src> && std::unsigned_integral<Dst>) {
            return val >= 0 && static_cast<std::make_unsigned_t<Src>>(val) <= std::numeric_limits<Dst>::max();
        } else {
            return val <= static_cast<std::make_unsigned_t<Dst>>(std::numeric_limits<Dst>::max());
        }
    }
}
