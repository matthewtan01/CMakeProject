cmake_minimum_required(VERSION 3.15)
project(app_project VERSION 0.1.0 LANGUAGES CXX)

# Collect source files
file(GLOB_RECURSE APP_SOURCES src/*.cpp)
file(GLOB_RECURSE APP_HEADERS include/*.h include/*.hpp)

# Create executable
add_executable(my_app ${APP_SOURCES} ${APP_HEADERS})

# C++ standard
target_compile_features(my_app PRIVATE cxx_std_17)

# Add UTF-8 support (needed for spdlog)
if (MSVC)
    target_compile_options(my_app PRIVATE /utf-8)
endif()

# Include directories for this project
target_include_directories(my_app PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_LIST_DIR}/../third_party/spdlog/include
    ${CMAKE_CURRENT_LIST_DIR}/../third_party/nlohmann/include
    ${CMAKE_CURRENT_LIST_DIR}/../third_party/httplib/include
)

# Define that we are using a header-only library
target_compile_definitions(my_app PRIVATE CPPHTTPLIB_NO_SSL)

# Link to lib_project
target_link_libraries(my_app PRIVATE my_library)

# Optional: Add default compiler warnings
if(MSVC)
    target_compile_options(my_app PRIVATE /W4)
else()
    target_compile_options(my_app PRIVATE -Wall -Wextra)
endif()

# Installation
include(GNUInstallDirs)
install(TARGETS my_app
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
