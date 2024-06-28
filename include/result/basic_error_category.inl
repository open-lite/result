#pragma once
#include "result/basic_error_category.hpp"

#if __cpp_if_constexpr >= 201606L
#define __OL_IF_CONSTEXPR constexpr
#else 
#define __OL_IF_CONSTEXPR
#endif


namespace ol {
    template<const char* Name, impl::desc_arr_str_type* DescArr, typename ErrEnum, int (*ErrcMapFn)(int)>
	const char*
    basic_error_category<Name, DescArr, ErrEnum, ErrcMapFn>::name() const noexcept {
		return Name;
	}

    template<const char* Name, impl::desc_arr_str_type* DescArr, typename ErrEnum, int (*ErrcMapFn)(int)>
	std::string 
    basic_error_category<Name, DescArr, ErrEnum, ErrcMapFn>::message(int c) const {
		if (c >= 0 && c < ErrEnum::num_codes)
			return std::string(DescArr[c]);

		return std::string(DescArr[ErrEnum::unknown]);
	}

    template<const char* Name, impl::desc_arr_str_type* DescArr, typename ErrEnum, int (*ErrcMapFn)(int)>
	std::error_condition 
    basic_error_category<Name, DescArr, ErrEnum, ErrcMapFn>::default_error_condition(int c) const noexcept {
        //TODO still needs proper testing for when ErrcMapFn != nullptr
		if (int mapped_c = impl::to_errc<ErrcMapFn>{}(c))
			return std::make_error_condition(static_cast<std::errc>(mapped_c));

		return std::error_condition(c, *this);
	}
}