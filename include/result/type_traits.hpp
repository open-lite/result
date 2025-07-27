#pragma once
#include <functional>
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



namespace ol {
namespace impl {
    template<typename T, typename BaseT>
    struct with_default_constructor : public BaseT {
        using BaseT::BaseT;
        constexpr with_default_constructor() noexcept : BaseT{OUTCOME_V2_NAMESPACE::in_place_type<T>} {}
    };

    template<typename T, typename BaseT>
    using select_result_base_default_ctor = std::conditional_t<std::is_default_constructible<T>::value, with_default_constructor<T, BaseT>, BaseT>;
}
}



#if __cpp_lib_is_invocable >= 201703L
namespace ol {
namespace impl {
    template <template<typename...> class TemplateT, typename T>
    struct is_specialization_of : std::false_type {};

    template <template<typename...> class TemplateT, typename... Args>
    struct is_specialization_of<TemplateT, TemplateT<Args...>> : std::true_type {};


    template <typename Fn, bool = std::is_invocable_v<Fn> && !is_specialization_of<result, Fn>::value>
    struct is_result_invocable : std::false_type {};
    template <typename Fn>
    struct is_result_invocable<Fn, true> : is_specialization_of<result, std::invoke_result_t<Fn>> {};
}
}
#endif
