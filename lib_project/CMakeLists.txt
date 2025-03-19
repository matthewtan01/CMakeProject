cmake_minimum_required(VERSION 3.15)
project(lib_project)

# Collect all source and header files
file(GLOB_RECURSE LIBRARY_SOURCES src/*.cpp)
file(GLOB_RECURSE LIBRARY_HEADERS include/*.h)

# Create the library
add_library(my_library STATIC ${LIBRARY_SOURCES})

# For spdlog
if (MSVC)
    target_compile_options(my_library PUBLIC /utf-8)
endif()


# For std::filesystem
target_compile_features(my_library PUBLIC cxx_std_17)

# Include directory for public headers
target_include_directories(my_library PUBLIC 
    include
    ${CMAKE_SOURCE_DIR}/third_party/spdlog/include
    ${CMAKE_SOURCE_DIR}/third_party/nlohmann/include
    ${CMAKE_SOURCE_DIR}/third_party/httplib/include
)

#${CMAKE_SOURCE_DIR} refers to the root directory of the project.

