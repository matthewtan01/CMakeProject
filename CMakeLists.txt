cmake_minimum_required(VERSION 3.15)
project(my_project VERSION 0.1.0 LANGUAGES CXX)

# Global C++ standard setting
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Build options
option(BUILD_TESTS "Build test suite" ON)

# Define build order with dependencies
add_subdirectory(lib_project)
add_subdirectory(app_project)

if(BUILD_TESTS)
    add_subdirectory(test_project)
endif()