#pragma once
#include <outcome/config.hpp>

namespace ol {
    template<typename T>
    using in_place_type_t = OUTCOME_V2_NAMESPACE::in_place_type_t<T>;
    using OUTCOME_V2_NAMESPACE::in_place_type;
}
