#pragma once
#include <cstddef>
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
    template<const char* Name, typename ErrEnum, std::string (*MsgFn)(int), int (*ErrcMapFn)(int)>
    struct basic_error_category : public std::error_category {
        constexpr basic_error_category() noexcept = default;
        virtual ~basic_error_category() = default;
        basic_error_category(const basic_error_category&) = delete;

		virtual inline const char* name() const noexcept override final;
		virtual inline std::string message(int c) const override;
		virtual inline std::error_condition default_error_condition(int c) const noexcept override;
    };
}

namespace ol {
namespace impl {
    template<std::string (*MsgFn)(int)>
    inline std::string msg_for(int c) noexcept;

    template<>
    inline std::string msg_for<nullptr>(int c) noexcept;


    template<int (*ErrcMapFn)(int)>
    constexpr int errc_for(int c) noexcept;

    template<>
    constexpr int errc_for<nullptr>(int c) noexcept;

    template<int (*ErrcMapFn)(int)>
    struct uses_general_category : std::bool_constant<ErrcMapFn != nullptr> {};
}
}


namespace ol {
    template<impl::desc_arr_str_type* Arr>
    std::string error_category_array(int c) { return std::string(Arr[c]); }
}

#include "result/basic_error_category.inl"
