#pragma once
#include <outcome.hpp>
#include <type_traits>


namespace ol {
    template<typename T>
    using in_place_type_t = OUTCOME_V2_NAMESPACE::in_place_type_t<T>;
    using OUTCOME_V2_NAMESPACE::in_place_type;
}


namespace ol {
    template<typename T, typename E> struct result;

    template<typename T>
    struct has_error_code : OUTCOME_V2_NAMESPACE::trait::is_error_code_available<std::decay_t<T>> {};


    template<typename FromT, typename FromE, typename ToT, typename ToE>
    struct is_convertible_from_error_code_to_enum {
        constexpr static bool value = 
            !std::is_same<std::decay_t<ToT>, std::decay_t<ToE>>::value &&
            !std::is_same<result<FromT, FromE>, result<ToT, ToE>>::value &&
            has_error_code<FromE>::value &&
            (std::is_convertible<int, ToE>::value || std::is_enum<ToE>::value) &&
            (std::is_void<FromT>::value || std::is_constructible<ToT, FromT>::value) &&
            (!std::is_void<FromE>::value && !std::is_constructible<ToE, FromE>::value) &&
            !std::is_constructible<ToE, typename has_error_code<FromE>::type>::value;
    };

    template<typename FromT, typename FromE, typename ToT, typename ToE>
    struct is_convertible_from_enum_to_error_code : is_convertible_from_error_code_to_enum<ToT, ToE, FromT, FromE> {};
}
