#pragma once

#ifdef __has_cpp_attribute 
    #if __has_cpp_attribute(nodiscard) >= 201907L
        #define __RESULT_NODISCARD(msg) [[nodiscard(msg)]]
    #elif __has_cpp_attribute(nodiscard)
        #define __RESULT_NODISCARD(msg) [[nodiscard]]
    #endif
#endif
#ifndef __RESULT_NODISCARD
    #define __RESULT_NODISCARD(msg)
#endif
 