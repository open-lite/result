#include "result.hpp"
#include <type_traits>


///// result<T, E> ////
namespace ol {
    #if __cpp_lib_expected >= 202202L
    template<typename T, typename E>
    template<class... Args>
    constexpr explicit result<T,E>::result(std::in_place_t, Args&&... args) 
        : result_base{in_place_type_t<T>{}, std::forward<Args>(args)...} {}

    template<typename T, typename E>
    template<class U, class... Args>
    constexpr explicit result<T,E>::result(std::in_place_t, std::initializer_list<U> il, Args&&... args)
        : result_base{in_place_type_t<T>{}, il, std::forward<Args>(args)...} {}


    template<typename T, typename E>
    template<class... Args>
    constexpr explicit result<T,E>::result(std::unexpect_t, Args&&... args)
        : result_base{in_place_type_t<E>{}, std::forward<Args>(args)...} {}

    template<typename T, typename E>
    template<class U, class... Args>
    constexpr explicit result<T,E>::result(std::unexpect_t, std::initializer_list<U> il, Args&&... args)
        : result_base{in_place_type_t<E>{}, il, std::forward<Args>(args)...} {}
    #endif
}


namespace ol {
    template<typename T, typename E>
    constexpr const T* result<T,E>::operator->() const noexcept { return &result_base<T,E>::assume_value(); }

    template<typename T, typename E>
    constexpr       T* result<T,E>::operator->()       noexcept { return &result_base<T,E>::assume_value(); }


    template<typename T, typename E>
    constexpr const T&  result<T,E>::operator*() const&  noexcept { return result_base<T,E>::assume_value(); }

    template<typename T, typename E>
    constexpr       T&  result<T,E>::operator*() &       noexcept { return result_base<T,E>::assume_value(); }

    template<typename T, typename E>
    constexpr const T&& result<T,E>::operator*() const&& noexcept { return result_base<T,E>::assume_value(); }

    template<typename T, typename E>
    constexpr       T&& result<T,E>::operator*() &&      noexcept { return result_base<T,E>::assume_value(); }
}

namespace ol {
    template<typename T, typename E>
    constexpr const E&  result<T,E>::error() const&  noexcept { return result_base<T,E>::assume_error(); }

    template<typename T, typename E>
    constexpr       E&  result<T,E>::error() &       noexcept { return result_base<T,E>::assume_error(); }

    template<typename T, typename E>
    constexpr const E&& result<T,E>::error() const&& noexcept { return result_base<T,E>::assume_error(); }

    template<typename T, typename E>
    constexpr       E&& result<T,E>::error() &&      noexcept { return result_base<T,E>::assume_error(); }
}

namespace ol {
    template<typename T, typename E>
    template<class U, typename std::enable_if<std::is_copy_constructible<U>::value && std::is_convertible<U&&, T>::value, bool>::type>
    constexpr T result<T,E>::value_or(U&& default_value) const& {
        return bool(*this) ? **this : static_cast<T>(std::forward<U>(default_value));
    }
    
    template<typename T, typename E>
    template<class U, typename std::enable_if<std::is_move_constructible<U>::value && std::is_convertible<U&&, T>::value, bool>::type>
    constexpr T result<T,E>::value_or(U&& default_value) && {
        return bool(*this) ? std::move(**this) : static_cast<T>(std::forward<U>(default_value));
    }
}


namespace ol {
    template<typename T, typename E>
    template<class... Args, typename std::enable_if<std::is_nothrow_constructible<T, Args...>::value, bool>::type>
    constexpr T& result<T,E>::emplace(Args&&... args) noexcept {
        *static_cast<result_base<T,E>*>(this) = result_base<T,E>{in_place_type<T>, std::forward<Args>(args)...};
        return *this;
    }

    template<typename T, typename E>
    template<class U, class... Args, typename std::enable_if<std::is_nothrow_constructible<T, std::initializer_list<U>&, Args...>::value, bool>::type>
    constexpr T& result<T,E>::emplace(std::initializer_list<U> il, Args&&... args) noexcept {
        *static_cast<result_base<T,E>*>(this) = result_base<T,E>{in_place_type<T>, il, std::forward<Args>(args)...};
        return *this;
    }
}



///// result<void, E> ////
namespace ol {
    #if __cpp_lib_expected >= 202202L
    template<typename E>
    constexpr explicit result<void,E>::result(std::in_place_t) 
        : result_base{in_place_type_t<void>{}} {}


    template<typename E>
    template<class... Args>
    constexpr explicit result<void,E>::result(std::unexpect_t, Args&&... args)
        : result_base{in_place_type_t<E>{}, std::forward<Args>(args)...} {}

    template<typename E>
    template<class U, class... Args>
    constexpr explicit result<void,E>::result(std::unexpect_t, std::initializer_list<U> il, Args&&... args)
        : result_base{in_place_type_t<E>{}, il, std::forward<Args>(args)...} {}
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
        return *this;
    }
}