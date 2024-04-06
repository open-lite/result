cmake_minimum_required(VERSION 3.15)

project(result VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)

add_library(${PROJECT_NAME} INTERFACE)
set_target_properties(${PROJECT_NAME} PROPERTIES 
    PUBLIC_HEADER "include/result.hpp"
    PRIVATE_HEADER "include/result.inl"
)


### include directory ###
cmake_path(SET SELF_INC_CMAKE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
file(TO_NATIVE_PATH "${SELF_INC_CMAKE_DIR}" SELF_INC_DIR)
target_include_directories(${PROJECT_NAME} INTERFACE "${SELF_INC_DIR}")
message(STATUS "Including self directory: ${SELF_INC_DIR}")


install(TARGETS ${PROJECT_NAME})