#pragma once
#include <system_error>
#include <type_traits>
#include <outcome/result.hpp>
#include <outcome/config.hpp>
#include <outcome/policy/terminate.hpp>

namespace ol {
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
    struct result : public result_base<T, E> {
        using result_base<T, E>::result_base;

        template<typename U = T, std::enable_if_t<std::is_default_constructible<U>::value, bool> = true>
        constexpr result() noexcept;

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
        using result_base<T, E>::operator=;

        using result_base<T, E>::operator bool;
        using result_base<T, E>::has_value;
        using result_base<T, E>::value;

        using result_base<T, E>::swap;
        using result_base<T, E>::operator==;
        using result_base<T, E>::operator!=;

    protected:
        using result_base<T, E>::has_error;
        using result_base<T, E>::has_exception;
        using result_base<T, E>::has_failure;
        using result_base<T, E>::has_lost_consistency;
        using result_base<T, E>::assume_error;
        using result_base<T, E>::assume_value;
        using result_base<T, E>::as_failure;
    };
}


namespace ol {
    template<typename E>
    struct result<void, E> : public result_base<void, E> {
        using result_base<void, E>::result_base;

        constexpr result() noexcept;

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

#include "result/result_type.inl"