#pragma once


#define OL_RESULT_DECLARE_AS_ERROR_CODE(type_ns, type_name, desc_arr, errc_map_arr, category_name) \
namespace type_ns { \
    namespace impl { constexpr static const char category_str[] = #category_name; } \
    using category = ::ol::basic_error_category<impl::category_str, desc_arr, type_name, errc_map_arr>; \
    inline std::error_code make_error_code(type_name e) { return { static_cast<int>(e), category()}; } \
    inline std::error_condition make_error_condition(type_name e) { return {static_cast<int>(e), category()}; } \
} \
\
namespace std { \
	template<> struct is_error_code_enum<type_ns::type_name> : true_type {}; \
	template<> struct is_error_condition_enum<type_ns::type_name> : true_type {}; \
} \
\
namespace OUTCOME_V2_NAMESPACE::trait { \
	template<> struct is_error_type<type_ns::type_name> { constexpr static bool value = true; }; \
} \
\
namespace type_ns { \
    extern inline const std::error_category& category_name##_category() noexcept { \
        static category c; \
        return c; \
    } \
}



#define OL_RESULT_DECLARE_AS_ERROR_CLASS(type_ns, type_name, code_fn)\
namespace type_ns { \
    inline std::error_code make_error_code(type_name e) { return make_error_code(e.code_fn); } \
    inline std::error_condition make_error_condition(type_name e) { return make_error_condition(e.code_fn); } \
} \
\
namespace OUTCOME_V2_NAMESPACE::trait { \
	template<> struct is_error_type<type_ns::type_name> { constexpr static bool value = true; }; \
    template<typename Enum> struct is_error_type_enum<type_ns::type_name, Enum> {  \
		constexpr static bool value = std::is_error_condition_enum<Enum>::value; \
	}; \
}