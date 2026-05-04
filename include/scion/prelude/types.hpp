#pragma once

#include "scion/core/types.hpp"

/// \file scion/prelude/types.hpp
/// \brief Re-exports the types in `scion/core/types.hpp` to the root namespace.
/// \note Do not import this file in library headers, only use it in source files or client code.

using u8 = scion::u8;
using u16 = scion::u16;
using u32 = scion::u32;
using u64 = scion::u64;
using usize = scion::usize;

using i8 = scion::i8;
using i16 = scion::i16;
using i32 = scion::i32;
using i64 = scion::i64;
using isize = scion::isize;

using f32 = scion::f32;
using f64 = scion::f64;
