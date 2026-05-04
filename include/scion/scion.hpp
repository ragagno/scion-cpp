#pragma once

#include "scion/core/core.hpp"
#include "scion/util/util.hpp"

#include <string>

/// \file scion/scion.hpp
/// \brief Main file of the library.

namespace scion {
    namespace version {
        inline constexpr scion::usize MAJOR = SCION_VERSION_MAJOR;
        inline constexpr scion::usize MINOR = SCION_VERSION_MINOR;
        inline constexpr scion::usize PATCH = SCION_VERSION_PATCH;
    }

    /// \brief Converts a size into a string representation.
    /// \param size Size to convert.
    /// \return Size with the appropriate unit.
    auto bytes_to_string(scion::usize size) -> std::string;
}
