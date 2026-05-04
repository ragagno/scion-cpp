#pragma once

#include "scion/core/types.hpp"

#include <concepts>
#include <tuple>
#include <memory>

/// \file scion/core/traits.hpp
/// \brief Provides trait-like construct for metaprogramming.

namespace scion {
    /// \brief Trait satisfied if the conversion from Src to Dst is lossless.
    /// @tparam Src Source type.
    /// @tparam Dst Destination type.
    template <std::integral Src, std::integral Dst>
    constexpr bool lossless_integral_conversion_v = (std::signed_integral<Src> == std::signed_integral<Dst> && std::numeric_limits<Src>::digits <= std::numeric_limits<Dst>::digits) || (std::unsigned_integral<Src> && std::signed_integral<Dst> && std::numeric_limits<Src>::digits < std::numeric_limits<Dst>::digits);

    /// \brief Concept for factory function output type.
    template<typename O, typename T>
    concept make_output = std::same_as<O, T> || std::same_as<O, T*> || std::same_as<O, std::unique_ptr<T>> || std::same_as<O, std::shared_ptr<T>>;

    template <typename T>
    struct is_uniform_tuple : std::false_type {};

    template <typename T, typename... Rest>
    struct is_uniform_tuple<std::tuple<T, Rest...>> : std::conjunction<std::is_same<T, Rest>...> {};

    template <typename T1, typename T2>
    struct is_uniform_tuple<std::pair<T1, T2>> : std::is_same<T1, T2> {};

    template <typename T, scion::usize N = 0>
    concept uniform_tuple = is_uniform_tuple<std::decay_t<T>>::value && (N == 0 || std::tuple_size_v<std::decay_t<T>> == N);
}
