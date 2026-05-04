#pragma once

#include <concepts>
#include <format>
#include <iostream>
#include <iterator>
#include <syncstream>
#include <utility>

/// \file scion/util/log.hpp
/// \brief Provides leveled logging capabilities.
///
/// Individual log levels can be disabled using their respective `SCION_NOLOG_XXX` compile definitions, or all at once using `SCION_NOLOGS`.
/// Implement your own library-level logging with the `SCION_IMPL_LOG_FUNCTION_ON` and `SCION_IMPL_LOG_FUNCTION_NO` macros.
/// ```
/// namespace yournamespace {
///     #ifndef YOUR_LIBRARY_NOLOG_ERROR
///         SCION_IMPL_LOG_FUNCTION_ON(error, scion::log::ANSI_ERROR)
///     #else
///         SCION_IMPL_LOG_FUNCTION_NO(error, scion::log::ANSI_ERROR)
///     #endif
/// }
/// ```

#ifndef SCION_NOCOLOR
    #define SCION_LOG_ANSI_CODE(code) code
#else
    #define SCION_LOG_ANSI_CODE(code) ""
#endif

#ifdef SCION_NOLOGS
    #define SCION_NOLOG_ERROR
    #define SCION_NOLOG_INFO
    #define SCION_NOLOG_WARN
    #define SCION_NOLOG_DEBUG
    #define SCION_NOLOG_TRACE
#endif

#define SCION_IMPL_LOG_FUNCTION_ON(name, ansi) template<typename... Args> void name(char const* prefix, std::format_string<Args...> fmt, Args&&... args) { scion::log::print(ansi, prefix, fmt, std::forward<Args>(args)...); }
#define SCION_IMPL_LOG_FUNCTION_NO(name, ansi) template<typename... Args> void name(char const*, std::format_string<Args...>, Args&&...) {}

namespace scion::log {
    inline constexpr char const * ANSI_ERROR = SCION_LOG_ANSI_CODE("\x1b[31;1m");
    inline constexpr char const * ANSI_WARN  = SCION_LOG_ANSI_CODE("\x1b[33;1m");
    inline constexpr char const * ANSI_INFO  = SCION_LOG_ANSI_CODE("\x1b[32;1m");
    inline constexpr char const * ANSI_DEBUG = SCION_LOG_ANSI_CODE("\x1b[34;1m");
    inline constexpr char const * ANSI_TRACE = SCION_LOG_ANSI_CODE("\x1b[90;1m");

    inline constexpr char const * ANSI_RESET = SCION_LOG_ANSI_CODE("\x1b[0m");

    template<typename... Args>
    void print(char const * prefix_modifier, char const * prefix, std::format_string<Args...> fmt, Args&&... args) {
        std::osyncstream synced{std::cout};

        if (prefix[0] != '\0') std::format_to(std::ostreambuf_iterator<char>(synced), "{}{}{} ", prefix_modifier, prefix, scion::log::ANSI_RESET);

        std::format_to(std::ostreambuf_iterator<char>(synced), fmt, std::forward<Args>(args)...);

        synced << "\n";
    }

    #ifndef SCION_NOLOG_ERROR
        SCION_IMPL_LOG_FUNCTION_ON(error, scion::log::ANSI_ERROR)
    #else
        SCION_IMPL_LOG_FUNCTION_NO(error, scion::log::ANSI_ERROR)
    #endif

    #ifndef SCION_NOLOG_WARN
        SCION_IMPL_LOG_FUNCTION_ON(warn, scion::log::ANSI_WARN)
    #else
        SCION_IMPL_LOG_FUNCTION_NO(warn, scion::log::ANSI_WARN)
    #endif

    #ifndef SCION_NOLOG_INFO
        SCION_IMPL_LOG_FUNCTION_ON(info, scion::log::ANSI_INFO)
    #else
        SCION_IMPL_LOG_FUNCTION_NO(info, scion::log::ANSI_INFO)
    #endif

    #ifndef SCION_NOLOG_DEBUG
        SCION_IMPL_LOG_FUNCTION_ON(debug, scion::log::ANSI_DEBUG)
    #else
        SCION_IMPL_LOG_FUNCTION_NO(debug, scion::log::ANSI_DEBUG)
    #endif

    #ifndef SCION_NOLOG_TRACE
        SCION_IMPL_LOG_FUNCTION_ON(trace, scion::log::ANSI_TRACE)
    #else
        SCION_IMPL_LOG_FUNCTION_NO(trace, scion::log::ANSI_TRACE)
    #endif
}
