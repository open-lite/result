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
    template<const char* Name, typename ErrEnum, std::string (*DescFn)(int) = nullptr, int (*ErrcMapFn)(int) = nullptr>
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
    template<impl::desc_arr_str_type* Arr>
    std::string error_category_array(int c) { return std::string(Arr[c]); }
}


namespace ol {
namespace impl {
    template<int (*ErrcMapFn)(int)>
    struct to_errc_fn {
        int operator()(int c) { return ErrcMapFn(c); }
    };
    template<> struct to_errc_fn<nullptr> {
        int operator()(int c) { return 0; }
    };

    template<std::string (*DescFn)(int)>
    struct get_desc_fn {
        std::string operator()(int c) { return DescFn(c); }
    };
    template<> struct get_desc_fn<nullptr> {
        std::string operator()(int c) { return ""; }
    };

    template<std::string (*DescFn)(int), int (*ErrcMapFn)(int)>
    struct category_fn {
        inline static int to_errc(int c) { return to_errc_fn<ErrcMapFn>{}(c); };
        inline static std::string get_desc(int c) { return get_desc_fn<DescFn>{}(c); };
    };
}
}
#include "result/basic_error_category.inl"
