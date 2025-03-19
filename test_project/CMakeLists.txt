cmake_minimum_required(VERSION 3.15)
project(test_project)

enable_testing()

add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/googletest googletest_build)

SET(TEST_SOURCES
	src/CurlHttpClientTest.cpp 
	src/FileSinkFactoryTest.cpp 
	src/HTTPLoggerTest.cpp 
	src/LogHelperTest.cpp 
	src/TCPLoggerTest.cpp 
	src/TCPSinkFactoryTest.cpp 
)

add_executable(test_project ${TEST_SOURCES})

target_include_directories(test_project PRIVATE
	${CMAKE_SOURCE_DIR}/test_project/include
	${CMAKE_SOURCE_DIR}/lib_project/include
	${CMAKE_SOURCE_DIR}/third_party/spdlog/include
	${CMAKE_SOURCE_DIR}/third_party/nlohmann/include
	${CMAKE_SOURCE_DIR}/third_party/googletest/googletest/include 
	${CMAKE_SOURCE_DIR}/third_party/googletest/googlemock/include
)
if (MSVC)
    add_compile_options(/utf-8)
endif()


target_link_libraries(test_project PRIVATE my_library)

target_link_libraries(test_project PRIVATE 
	gtest 
	gtest_main
	gmock
	gmock_main
)

add_test(NAME MyTests COMMAND test_project)


