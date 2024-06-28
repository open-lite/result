cmake_minimum_required(VERSION 3.15)

project(result VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)

add_library(${PROJECT_NAME} INTERFACE)
set_target_properties(${PROJECT_NAME} PROPERTIES 
    PUBLIC_HEADER "include/${PROJECT_NAME}.hpp"
)
set(${PROJECT_NAME}_HEADER_FILES
    "result_type.hpp"
    "result_type.inl"

    "basic_error_category.hpp"
    "basic_error_category.inl"

    "in_place_type.hpp"

    "declare_error_code.h"
)

list(TRANSFORM ${PROJECT_NAME}_HEADER_FILES PREPEND "include/${PROJECT_NAME}/")
target_sources(${PROJECT_NAME} PUBLIC FILE_SET ${PROJECT_NAME}_HEADERS TYPE HEADERS BASE_DIRS "include" FILES ${${PROJECT_NAME}_HEADER_FILES})


### include directory ###
cmake_path(SET SELF_INC_CMAKE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
file(TO_NATIVE_PATH "${SELF_INC_CMAKE_DIR}" SELF_INC_DIR)
target_include_directories(${PROJECT_NAME} INTERFACE "${SELF_INC_DIR}")
message(STATUS "Including self directory: ${SELF_INC_DIR}")


install(TARGETS ${PROJECT_NAME} FILE_SET ${PROJECT_NAME}_HEADERS)