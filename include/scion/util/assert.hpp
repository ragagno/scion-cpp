#pragma once

#include <stdexcept>
#include <source_location>

#include "scion/constants.hpp"

/// \file scion/util/assert.hpp
/// \brief Provides debug assertion tooling.

namespace scion {
    inline constexpr bool ENABLE_ASSERTIONS = scion::configuration::DEBUG || scion::configuration::PROFILE;

    /// \brief Aborts execution if the given boolean is false and debug assertions are enabled.
    /// \param condition Condition to check.
    /// \param message Message to display if the condition is false.
    /// \param location Source location to display in the error message.
    /// \panics if the given condition is false and debug assertions are enabled.
    /// \note If this function is called in a consteval context, the condition will always be checked, even if debug assertions are disabled.
    constexpr void assert_debug(bool const condition, char const* const message = nullptr, std::source_location const location = std::source_location::current()) noexcept {
        if consteval {
            // NOTE throw in noexcept is fine for consteval contexts
            if (!condition) throw std::runtime_error(message ? message : "assertion failed");
        } else {
            if constexpr (ENABLE_ASSERTIONS) {
                if (!condition) {
                    std::fprintf(stderr, "assertion failed at %s:%d: %s\n", location.file_name(), location.line(), message ? message : "(no message)");
                    std::abort();
                }
            }
        }
    }
}
