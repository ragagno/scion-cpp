#pragma once

/// \file scion/constants.hpp
/// \brief Provides library macros and other symbols.

#define SCION_VERSION_MAJOR @PROJECT_VERSION_MAJOR@
#define SCION_VERSION_MINOR @PROJECT_VERSION_MINOR@
#define SCION_VERSION_PATCH @PROJECT_VERSION_PATCH@

namespace scion {
    namespace platform {
#ifdef SCION_PLATFORM_WINDOWS
        inline constexpr bool WINDOWS = true;
#else
        inline constexpr bool WINDOWS = false;
#endif

#ifdef SCION_PLATFORM_LINUX
        inline constexpr bool LINUX = true;
#else
        inline constexpr bool LINUX = false;
#endif

#ifdef SCION_PLATFORM_MAC
        inline constexpr bool MAC = true;
#else
        inline constexpr bool MAC = false;
#endif

        static_assert(WINDOWS + LINUX + MAC <= 1, "incoherent platform macros");
    }

    namespace compiler {
#ifdef SCION_COMPILER_CLANG
        inline constexpr bool CLANG = true;
#else
        inline constexpr bool CLANG = false;
#endif

#ifdef SCION_COMPILER_MSVC
        inline constexpr bool MSVC = true;
#else
        inline constexpr bool MSVC = false;
#endif

#ifdef SCION_COMPILER_GCC
        inline constexpr bool GCC = true;
#else
        inline constexpr bool GCC = false;
#endif

        static_assert(CLANG + MSVC + GCC <= 1, "incoherent compiler macros");
    }

    namespace configuration {
#ifdef SCION_CONFIGURATION_RELEASE
        inline constexpr bool RELEASE = true;
#else
        inline constexpr bool RELEASE = false;
#endif

#if defined(SCION_CONFIGURATION_PROFILE) || !defined(SCION_CONFIGURATION_RELEASE) && !defined(SCION_CONFIGURATION_DEBUG)
        inline constexpr bool PROFILE = true;
#else
        inline constexpr bool PROFILE = false;
#endif

#ifdef SCION_CONFIGURATION_DEBUG
        inline constexpr bool DEBUG = true;
#else
        inline constexpr bool DEBUG = false;
#endif

        static_assert(RELEASE + PROFILE + DEBUG == 1, "incoherent configuration macros");
    }
}
