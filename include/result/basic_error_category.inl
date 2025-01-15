#pragma once
#include "result/basic_error_category.hpp"
#include <system_error>

namespace ol {
    template<const char* Name, typename ErrEnum, std::string (*MsgFn)(int), int (*ErrcMapFn)(int)>
	const char*
    basic_error_category<Name, ErrEnum, MsgFn, ErrcMapFn>::name() const noexcept {
		return Name;
	}

    template<const char* Name, typename ErrEnum, std::string (*MsgFn)(int), int (*ErrcMapFn)(int)>
	std::string 
    basic_error_category<Name, ErrEnum, MsgFn, ErrcMapFn>::message(int c) const {
		return impl::msg_for<MsgFn>(c);
	}

    template<const char* Name, typename ErrEnum, std::string (*MsgFn)(int), int (*ErrcMapFn)(int)>
	std::error_condition 
    basic_error_category<Name, ErrEnum, MsgFn, ErrcMapFn>::default_error_condition(int c) const noexcept {
		return std::error_condition(impl::errc_for<ErrcMapFn>(c), impl::uses_general_category<ErrcMapFn>::value ? std::generic_category() : *this);
	}
}

namespace ol{
namespace impl{
    template<std::string (*MsgFn)(int)>
    std::string msg_for(int c) noexcept {
		return MsgFn(c);
	}

    template<>
    std::string msg_for<nullptr>(int c) noexcept {
		return std::string("<no error messages are provided>");
	}


    template<int (*ErrcMapFn)(int)>
    constexpr int errc_for(int c) noexcept {
		return ErrcMapFn(c);
	}

    template<>
    constexpr int errc_for<nullptr>(int c) noexcept {
		return c;
	}
}
}