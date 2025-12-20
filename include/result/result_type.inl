#pragma once
#include "result/result_type.hpp"
#include <type_traits>


///// result<T, E> ////
namespace ol {
    template<typename T, typename E>
    template<typename U, typename G, typename P, std::enable_if_t<is_convertible_from_error_code_to_enum<U, G, T, E>::value, bool>>
    constexpr result<T,E>::result(const basic_result_base<U, G, P>& other) noexcept : result_base<T,E>{other.has_value() ? 
        result_base<T,E>{in_place_type<T>, other.assume_value()} :
        result_base<T,E>{in_place_type<E>, static_cast<E>(other.assume_error().value())} } {}

    template<typename T, typename E>
    template<typename U, typename G, typename P, std::enable_if_t<is_convertible_from_error_code_to_enum<U, G, T, E>::value, bool>>
    constexpr result<T,E>::result(basic_result_base<U, G, P>&& other) noexcept : result_base<T,E>{other.has_value() ? 
        result_base<T,E>{in_place_type<T>, std::move(other).assume_value()} :
        result_base<T,E>{in_place_type<E>, static_cast<E>(std::move(other).assume_error().value())} } {}

    template<typename T, typename E>
    template<typename U, typename G, typename P, std::enable_if_t<is_convertible_from_enum_to_error_code<U, G, T, E>::value, bool>>
    constexpr result<T,E>::result(const basic_result_base<U, G, P>& other) noexcept : result_base<T,E>{other.has_value() ? 
        result_base<T,E>{in_place_type<T>, other.assume_value()} :
        result_base<T,E>{in_place_type<E>, make_error_code(other.assume_error())} } {}

    template<typename T, typename E>
    template<typename U, typename G, typename P, std::enable_if_t<is_convertible_from_enum_to_error_code<U, G, T, E>::value, bool>>
    constexpr result<T,E>::result(basic_result_base<U, G, P>&& other) noexcept : result_base<T,E>{other.has_value() ? 
        result_base<T,E>{in_place_type<T>, std::move(other).assume_value()} :
        result_base<T,E>{in_place_type<E>, make_error_code(std::move(other).assume_error())} } {}
}

namespace ol {
    #if __cpp_lib_expected >= 202202L
    template<typename T, typename E>
    template<class... Args>
    constexpr result<T,E>::result(std::in_place_t, Args&&... args) noexcept 
        : result_base<T,E>{in_place_type_t<T>{}, std::forward<Args>(args)...} {}

    template<typename T, typename E>
    template<class U, class... Args>
    constexpr result<T,E>::result(std::in_place_t, std::initializer_list<U> il, Args&&... args) noexcept
        : result_base<T,E>{in_place_type_t<T>{}, il, std::forward<Args>(args)...} {}


    template<typename T, typename E>
    template<class... Args>
    constexpr result<T,E>::result(std::unexpect_t, Args&&... args) noexcept
        : result_base<T,E>{in_place_type_t<E>{}, std::forward<Args>(args)...} {}

    template<typename T, typename E>
    template<class U, class... Args>
    constexpr result<T,E>::result(std::unexpect_t, std::initializer_list<U> il, Args&&... args) noexcept
        : result_base<T,E>{in_place_type_t<E>{}, il, std::forward<Args>(args)...} {}
    #endif
}


namespace ol {
    template<typename T, typename E>
    constexpr const T* result<T,E>::operator->() const noexcept { return &result_base<T, E>::assume_value(); }

    template<typename T, typename E>
    constexpr       T* result<T,E>::operator->()       noexcept { return &result_base<T, E>::assume_value(); }


    template<typename T, typename E>
    constexpr const T&  result<T,E>::operator*() const&  noexcept { return result_base<T, E>::assume_value(); }

    template<typename T, typename E>
    constexpr       T&  result<T,E>::operator*() &       noexcept { return result_base<T, E>::assume_value(); }

    template<typename T, typename E>
    constexpr const T&& result<T,E>::operator*() const&& noexcept { return std::move(*this).assume_value(); }

    template<typename T, typename E>
    constexpr       T&& result<T,E>::operator*() &&      noexcept { return std::move(*this).assume_value(); }
}

namespace ol {
    template<typename T, typename E>
    constexpr const E&  result<T,E>::error() const&  noexcept { return result_base<T, E>::assume_error(); }

    template<typename T, typename E>
    constexpr       E&  result<T,E>::error() &       noexcept { return result_base<T, E>::assume_error(); }

    template<typename T, typename E>
    constexpr const E&& result<T,E>::error() const&& noexcept { return std::move(*this).assume_error(); }

    template<typename T, typename E>
    constexpr       E&& result<T,E>::error() &&      noexcept { return std::move(*this).assume_error(); }
}

namespace ol {
    template<typename T, typename E>
    template<class U, std::enable_if_t<std::is_copy_constructible<U>::value && std::is_convertible<U&&, T>::value, bool>>
    constexpr T result<T,E>::value_or(U&& default_value) const& noexcept {
        return bool(*this) ? **this : static_cast<T>(std::forward<U>(default_value));
    }
    
    template<typename T, typename E>
    template<class U, std::enable_if_t<std::is_move_constructible<U>::value && std::is_convertible<U&&, T>::value, bool>>
    constexpr T result<T,E>::value_or(U&& default_value) && noexcept {
        return bool(*this) ? std::move(**this) : static_cast<T>(std::forward<U>(default_value));
    }
}


namespace ol {
    template<typename T, typename E>
    template<class... Args, std::enable_if_t<std::is_nothrow_constructible<T, Args...>::value, bool>>
    constexpr T& result<T,E>::emplace(Args&&... args) noexcept {
        *static_cast<result_base<T,E>*>(this) = result_base<T,E>{in_place_type<T>, std::forward<Args>(args)...};
        return *this;
    }

    template<typename T, typename E>
    template<class U, class... Args, std::enable_if_t<std::is_nothrow_constructible<T, std::initializer_list<U>&, Args...>::value, bool>>
    constexpr T& result<T,E>::emplace(std::initializer_list<U> il, Args&&... args) noexcept {
        *static_cast<result_base<T,E>*>(this) = result_base<T,E>{in_place_type<T>, il, std::forward<Args>(args)...};
        return *this;
    }
}



///// result<void, E> ////
namespace ol {
    template<typename E>
    constexpr result<void,E>::result() noexcept
        : result_base<void,E>{in_place_type_t<void>{}} {}
}


namespace ol {
    template<typename E>
    template<typename G, typename P, std::enable_if_t<is_convertible_from_error_code_to_enum<void, G, void, E>::value, bool>>
    constexpr result<void,E>::result(const basic_result_base<void, G, P>& other) noexcept : result_base<void,E>{other.has_value() ? 
        result_base<void,E>{in_place_type<void>} :
        result_base<void,E>{in_place_type<E>, static_cast<E>(other.assume_error().value())} } {}

    template<typename E>
    template<typename G, typename P, std::enable_if_t<is_convertible_from_error_code_to_enum<void, G, void, E>::value, bool>>
    constexpr result<void,E>::result(basic_result_base<void, G, P>&& other) noexcept : result_base<void,E>{other.has_value() ? 
        result_base<void,E>{in_place_type<void>} :
        result_base<void,E>{in_place_type<E>, static_cast<E>(std::move(other).assume_error().value())} } {}

    template<typename E>
    template<typename G, typename P, std::enable_if_t<is_convertible_from_enum_to_error_code<void, G, void, E>::value, bool>>
    constexpr result<void,E>::result(const basic_result_base<void, G, P>& other) noexcept : result_base<void,E>{other.has_value() ? 
        result_base<void,E>{in_place_type<void>} :
        result_base<void,E>{in_place_type<E>, make_error_code(other.assume_error())} } {}

    template<typename E>
    template<typename G, typename P, std::enable_if_t<is_convertible_from_enum_to_error_code<void, G, void, E>::value, bool>>
    constexpr result<void,E>::result(basic_result_base<void, G, P>&& other) noexcept : result_base<void,E>{other.has_value() ? 
        result_base<void,E>{in_place_type<void>} :
        result_base<void,E>{in_place_type<E>, make_error_code(std::move(other).assume_error())} } {}
}

namespace ol {
    #if __cpp_lib_expected >= 202202L
    template<typename E>
    constexpr result<void,E>::result(std::in_place_t) noexcept 
        : result_base<void,E>{in_place_type_t<void>{}} {}


    template<typename E>
    template<class... Args>
    constexpr result<void,E>::result(std::unexpect_t, Args&&... args) noexcept
        : result_base<void,E>{in_place_type_t<E>{}, std::forward<Args>(args)...} {}

    template<typename E>
    template<class U, class... Args>
    constexpr result<void,E>::result(std::unexpect_t, std::initializer_list<U> il, Args&&... args) noexcept
        : result_base<void,E>{in_place_type_t<E>{}, il, std::forward<Args>(args)...} {}
    #endif
}


namespace ol {
    template<typename E>
    constexpr void result<void,E>::operator*() const noexcept { return result_base<void,E>::assume_value(); }
}

namespace ol {
    template<typename E>
    constexpr const E&  result<void,E>::error() const&  noexcept { return result_base<void,E>::assume_error(); }

    template<typename E>
    constexpr       E&  result<void,E>::error() &       noexcept { return result_base<void,E>::assume_error(); }

    template<typename E>
    constexpr const E&& result<void,E>::error() const&& noexcept { return result_base<void,E>::assume_error(); }

    template<typename E>
    constexpr       E&& result<void,E>::error() &&      noexcept { return result_base<void,E>::assume_error(); }
}


namespace ol {
    template<typename E>
    constexpr void result<void,E>::emplace() noexcept {
        *static_cast<result_base<void,E>*>(this) = result_base<void,E>{in_place_type<void>};
    }
}



#if __cpp_lib_is_invocable >= 201703L
template<typename LeftResultCallable, typename RightResultCallable, std::enable_if_t<ol::impl::is_result_invocable<LeftResultCallable&&>::value && ol::impl::is_result_invocable<RightResultCallable&&>::value, bool>>
constexpr auto operator&&(LeftResultCallable&& lhs, RightResultCallable&& rhs) noexcept -> std::common_type_t<std::invoke_result_t<LeftResultCallable&&>, std::invoke_result_t<RightResultCallable&&>> {
    auto lhs_result = std::forward<LeftResultCallable>(lhs)();
    if(!lhs_result.has_value()) return lhs_result;
    return std::forward<RightResultCallable>(rhs)();
}

template<typename T, typename E, typename ResultCallable, std::enable_if_t<ol::impl::is_result_invocable<ResultCallable&&>::value, bool>>
constexpr ol::result<T,E> operator&&(ol::result<T,E> const& lhs, ResultCallable&& rhs) noexcept {
    if(!lhs.has_value()) return lhs;
    return std::forward<ResultCallable>(rhs)();
}

template<typename ResultCallable, typename T, typename E, std::enable_if_t<ol::impl::is_result_invocable<ResultCallable&&>::value, bool>>
constexpr ol::result<T,E> operator&&(ResultCallable&& lhs, ol::result<T, E> const& rhs) noexcept {
    auto lhs_result = std::forward<ResultCallable>(lhs)();
    if(!lhs_result.has_value()) return lhs_result;
    return rhs;
}
#endif
