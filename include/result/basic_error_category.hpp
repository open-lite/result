#pragma once
#include <system_error>
#include <type_traits>


namespace ol {
namespace impl {
#if __cpp_lib_string_view >= 201606L
using desc_arr_str_type = const std::string_view;
#else 
using desc_arr_str_type = char const*;
#endif
}
}



namespace ol {
    template<const char* Name, impl::desc_arr_str_type* DescArr, typename ErrEnum, int (*ErrcMapFn)(int) = nullptr>
    struct basic_error_category : public std::error_category {
        constexpr basic_error_category() noexcept = default;
        virtual ~basic_error_category() = default;
        basic_error_category(const basic_error_category&) = delete;

		virtual inline const char* name() const noexcept override final;
		virtual inline std::string message(int c) const override final;
		virtual inline std::error_condition default_error_condition(int c) const noexcept override final;
    };
}



namespace ol {
namespace impl {
    template<int (*ErrcMapFn)(int)>
    struct to_errc {
        int operator()(int c) { return ErrcMapFn(c); }
    };

    template<> struct to_errc<nullptr> {
        int operator()(int c) { return 0; }
    };
}
}
#include "result/basic_error_category.inl"
