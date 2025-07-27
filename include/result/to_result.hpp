#pragma once
#include <type_traits>
#include <functional>
#if __cpp_lib_invoke >= 201411L && __cpp_lib_is_invocable >= 201703L
#include "result/result_type.hpp"
#include "result/type_traits.hpp"

namespace ol {
    template<typename ResultCallable, std::enable_if_t<impl::is_result_invocable<ResultCallable&&>::value, bool> = true>
    constexpr std::invoke_result_t<ResultCallable&&> to_result(ResultCallable&& callable) { return std::invoke(std::forward<ResultCallable>(callable)); }

    template<typename T, typename E>
    constexpr result<T, E> to_result(result<T, E>& r) noexcept { return r; }
    template<typename T, typename E>
    constexpr result<T, E> to_result(result<T, E>&& r) noexcept { return std::move(r); }
}
#endif