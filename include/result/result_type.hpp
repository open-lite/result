#pragma once
#include <system_error>
#include <type_traits>
#include <outcome/result.hpp>
#include <outcome/config.hpp>
#include <outcome/policy/terminate.hpp>
#include "result/type_traits.hpp"
#include "result/nodiscard.h"
#include "type_traits.hpp"

namespace ol {
    template<typename T, typename E, typename P>
    using basic_result_base = OUTCOME_V2_NAMESPACE::result<T, E, P>;

#if __cpp_exceptions
    template<typename T, typename E>
    using result_base = OUTCOME_V2_NAMESPACE::checked<T, E>;
#else
    template<typename T, typename E>
    using result_base = OUTCOME_V2_NAMESPACE::result<T, E, OUTCOME_V2_NAMESPACE::policy::terminate>;
#endif
}


namespace ol {
    template<typename T, typename E = std::error_code>
    class __RESULT_NODISCARD("Return type is a non-void result - it should be verified and extracted with RESULT_TRY_*") 
    result : public impl::select_result_base_default_ctor<T, result_base<T,E>> {
        using base_type = impl::select_result_base_default_ctor<T, result_base<T,E>>;
    public:
        using base_type::base_type;

        template<typename U, typename G, typename P, std::enable_if_t<is_convertible_from_error_code_to_enum<U, G, T, E>::value, bool> = true>
        constexpr result(const basic_result_base<U, G, P>& other);
        template<typename U, typename G, typename P, std::enable_if_t<is_convertible_from_error_code_to_enum<U, G, T, E>::value, bool> = true>
        constexpr result(basic_result_base<U, G, P>&& other);
        template<typename U, typename G, typename P, std::enable_if_t<is_convertible_from_enum_to_error_code<U, G, T, E>::value, bool> = true>
        constexpr result(const basic_result_base<U, G, P>& other);
        template<typename U, typename G, typename P, std::enable_if_t<is_convertible_from_enum_to_error_code<U, G, T, E>::value, bool> = true>
        constexpr result(basic_result_base<U, G, P>&& other);

        #if __cpp_lib_expected >= 202202L
        template<class... Args>
        constexpr explicit result(std::in_place_t, Args&&... args);
        template<class U, class... Args>
        constexpr explicit result(std::in_place_t, std::initializer_list<U> il, Args&&... args);
        
        template<class... Args>
        constexpr explicit result(std::unexpect_t, Args&&... args);
        template<class U, class... Args>
        constexpr explicit result(std::unexpect_t, std::initializer_list<U> il, Args&&... args);
        #endif


        constexpr const T* operator->() const noexcept;
        constexpr       T* operator->()       noexcept;
        constexpr const T&  operator*() const&  noexcept;
        constexpr       T&  operator*() &       noexcept;
        constexpr const T&& operator*() const&& noexcept;
        constexpr       T&& operator*() &&      noexcept;
        
        constexpr const E&  error() const&  noexcept;
        constexpr       E&  error() &       noexcept;
        constexpr const E&& error() const&& noexcept;
        constexpr       E&& error() &&      noexcept;
        
        template<class U, std::enable_if_t<std::is_copy_constructible<U>::value && std::is_convertible<U&&, T>::value, bool> = true>
        constexpr T value_or(U&& default_value) const&;
        template<class U, std::enable_if_t<std::is_move_constructible<U>::value && std::is_convertible<U&&, T>::value, bool> = true>
        constexpr T value_or(U&& default_value) &&;


        template<class... Args, std::enable_if_t<std::is_nothrow_constructible<T, Args...>::value, bool> = true>
        constexpr T& emplace(Args&&... args ) noexcept;
        template<class U, class... Args, std::enable_if_t<std::is_nothrow_constructible<T, std::initializer_list<U>&, Args...>::value, bool> = true>
        constexpr T& emplace(std::initializer_list<U> il, Args&&... args ) noexcept;


    public:
        using base_type::operator=;

        using base_type::operator bool;
        using base_type::has_value;
        using base_type::value;

        using base_type::swap;
        using base_type::operator==;
        using base_type::operator!=;

    protected:
        using base_type::has_error;
        using base_type::has_exception;
        using base_type::has_failure;
        using base_type::has_lost_consistency;
        using base_type::assume_error;
        using base_type::assume_value;
        using base_type::as_failure;
    };
}


namespace ol {
    template<typename E>
    class __RESULT_NODISCARD("Return type is a result - it should be verified with RESULT_VERIFY") result<void, E> : public result_base<void, E> {
    public:
        using result_base<void, E>::result_base;

        constexpr result() noexcept;

        template<typename G, typename P, std::enable_if_t<is_convertible_from_error_code_to_enum<void, G, void, E>::value, bool> = true>
        constexpr result(const basic_result_base<void, G, P>& other);
        template<typename G, typename P, std::enable_if_t<is_convertible_from_error_code_to_enum<void, G, void, E>::value, bool> = true>
        constexpr result(basic_result_base<void, G, P>&& other);
        template<typename G, typename P, std::enable_if_t<is_convertible_from_enum_to_error_code<void, G, void, E>::value, bool> = true>
        constexpr result(const basic_result_base<void, G, P>& other);
        template<typename G, typename P, std::enable_if_t<is_convertible_from_enum_to_error_code<void, G, void, E>::value, bool> = true>
        constexpr result(basic_result_base<void, G, P>&& other);

        #if __cpp_lib_expected >= 202202L
        constexpr explicit result(std::in_place_t) noexcept;
        
        template<class... Args>
        constexpr explicit result(std::unexpect_t, Args&&... args);
        template<class U, class... Args>
        constexpr explicit result(std::unexpect_t, std::initializer_list<U> il, Args&&... args);
        #endif


        constexpr void operator*() const noexcept;

        using result_base<void, E>::operator bool;
        using result_base<void, E>::has_value;

        
        constexpr const E&  error() const&  noexcept;
        constexpr       E&  error() &       noexcept;
        constexpr const E&& error() const&& noexcept;
        constexpr       E&& error() &&      noexcept;


        constexpr void emplace() noexcept;


    public:
        using result_base<void, E>::operator=;

        using result_base<void, E>::value;

        using result_base<void, E>::swap;
        using result_base<void, E>::operator==;
        using result_base<void, E>::operator!=;

    protected:
        using result_base<void, E>::has_error;
        using result_base<void, E>::has_exception;
        using result_base<void, E>::has_failure;
        using result_base<void, E>::has_lost_consistency;
        using result_base<void, E>::assume_error;
        using result_base<void, E>::assume_value;
        using result_base<void, E>::as_failure;
    };
}


#if __cpp_lib_is_invocable >= 201703L
template<typename LeftResultCallable, typename RightResultCallable, std::enable_if_t<ol::impl::is_result_invocable<LeftResultCallable&&>::value && ol::impl::is_result_invocable<RightResultCallable&&>::value, bool> = true>
constexpr auto operator&&(LeftResultCallable&& lhs, RightResultCallable&& rhs) -> std::common_type_t<std::invoke_result_t<LeftResultCallable&&>, std::invoke_result_t<RightResultCallable&&>>;

template<typename T, typename E, typename ResultCallable, std::enable_if_t<ol::impl::is_result_invocable<ResultCallable&&>::value, bool> = true>
constexpr ol::result<T, E> operator&&(ol::result<T, E> const& lhs, ResultCallable&& rhs);

template<typename ResultCallable, typename T, typename E, std::enable_if_t<ol::impl::is_result_invocable<ResultCallable&&>::value, bool> = true>
constexpr ol::result<T, E> operator&&(ResultCallable&& lhs, ol::result<T, E> const& rhs);
#endif

#include "result/result_type.inl"