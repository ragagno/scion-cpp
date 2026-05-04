#pragma once

#include <cstdint>
#include <limits>
#include <type_traits>

/// \file scion/core/types.hpp
/// \brief Provides platform-independent primitive types.

namespace scion {
    /// \brief 8 bits unsigned integer
    using u8 = std::uint8_t;
    /// \brief 16 bits unsigned integer
    using u16 = std::uint16_t;
    /// \brief 32 bits unsigned integer
    using u32 = std::uint32_t;
    /// \brief 64 bits unsigned integer
    using u64 = std::uint64_t;
    /// \brief pointer-sized (not function pointer) unsigned integer
    using usize = std::uintptr_t;

    /// \brief 8 bits signed integer
    using i8 = std::int8_t;
    /// \brief 16 bits signed integer
    using i16 = std::int16_t;
    /// \brief 32 bits signed integer
    using i32 = std::int32_t;
    /// \brief 64 bits signed integer
    using i64 = std::int64_t;
    /// \brief pointer-sized (not function pointer) signed integer
    using isize = std::intptr_t;

    /// \brief binary32 IEEE 754 type
    using f32 = float;
    /// \brief binary64 IEEE 754 type
    using f64 = std::conditional_t<sizeof(double) == 8, double, long double>;
}

static_assert(std::numeric_limits<unsigned char>::digits == 8, "non-octet byte platforms are not supported");

static_assert(std::numeric_limits<scion::u8>::digits == 8, "u8 is not 8 bits");
static_assert(std::numeric_limits<scion::u16>::digits == 16, "u16 is not 16 bits");
static_assert(std::numeric_limits<scion::u32>::digits == 32, "u32 is not 32 bits");
static_assert(std::numeric_limits<scion::u64>::digits == 64, "u64 is not 64 bits");

static_assert(std::numeric_limits<scion::i8>::digits == 7, "i8 does not have 7 value bits");
static_assert(std::numeric_limits<scion::i16>::digits == 15, "i16 does not have 15 value bits");
static_assert(std::numeric_limits<scion::i32>::digits == 31, "i32 does not have 31 value bits");
static_assert(std::numeric_limits<scion::i64>::digits == 63, "i64 does not have 63 value bits");

static_assert(sizeof(scion::usize) == sizeof(void*), "usize is not exactly as wide as sizeof(void*)");
static_assert(sizeof(scion::isize) == sizeof(void*), "isize is not exactly as wide as sizeof(void*)");

static_assert(!std::numeric_limits<scion::u8>::is_signed, "u8 is not unsigned");
static_assert(!std::numeric_limits<scion::u16>::is_signed, "u16 is not unsigned");
static_assert(!std::numeric_limits<scion::u32>::is_signed, "u32 is not unsigned");
static_assert(!std::numeric_limits<scion::u64>::is_signed, "u64 is not unsigned");
static_assert(!std::numeric_limits<scion::usize>::is_signed, "usize is not unsigned");

static_assert(std::numeric_limits<scion::i8>::is_signed, "i8 is not signed");
static_assert(std::numeric_limits<scion::i16>::is_signed, "i16 is not signed");
static_assert(std::numeric_limits<scion::i32>::is_signed, "i32 is not signed");
static_assert(std::numeric_limits<scion::i64>::is_signed, "i64 is not signed");
static_assert(std::numeric_limits<scion::isize>::is_signed, "isize is not signed");

static_assert(sizeof(scion::f32) * std::numeric_limits<unsigned char>::digits == 32, "f32 is not 32 bits");
static_assert(sizeof(scion::f64) * std::numeric_limits<unsigned char>::digits == 64, "f64 is not 64 bits");

static_assert(std::numeric_limits<scion::f32>::is_iec559, "f32 is not IEC 559 / IEEE 754");
static_assert(std::numeric_limits<scion::f64>::is_iec559, "f64 is not IEC 559 / IEEE 754");

static_assert(std::numeric_limits<scion::f32>::digits == 24, "f32 is not binary32 precision");
static_assert(std::numeric_limits<scion::f64>::digits == 53, "f64 is not binary64 precision");
