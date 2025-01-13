#pragma once
#include "result/basic_error_category.hpp"

#if __cpp_if_constexpr >= 201606L
#define __OL_IF_CONSTEXPR constexpr
#else 
#define __OL_IF_CONSTEXPR
#endif


namespace ol {
    template<const char* Name, typename ErrEnum, std::string (*DescFn)(int), int (*ErrcMapFn)(int)>
	const char*
    basic_error_category<Name, ErrEnum, DescFn, ErrcMapFn>::name() const noexcept {
		return Name;
	}

    template<const char* Name, typename ErrEnum, std::string (*DescFn)(int), int (*ErrcMapFn)(int)>
	std::string 
    basic_error_category<Name, ErrEnum, DescFn, ErrcMapFn>::message(int c) const {
		if (c < 0 || c >= static_cast<int>(ErrEnum::num_codes)) 
			std::string("<unknown error code; no message available>");

		std::string msg = impl::category_fn<DescFn, ErrcMapFn>::get_desc(c);
		if (!msg.empty())
			return msg;
		return std::string("<no message provided for given error code>");
	}

    template<const char* Name, typename ErrEnum, std::string (*DescFn)(int), int (*ErrcMapFn)(int)>
	std::error_condition 
    basic_error_category<Name, ErrEnum, DescFn, ErrcMapFn>::default_error_condition(int c) const noexcept {
		if (int mapped_c = impl::category_fn<DescFn, ErrcMapFn>::to_errc(c))
			return std::make_error_condition(static_cast<std::errc>(mapped_c));

		return std::error_condition(c, *this);
	}
}