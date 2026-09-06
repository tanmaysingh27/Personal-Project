cmake_minimum_required(VERSION 3.10)
project(mylib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Linking Library
add_library(mylib INTERFACE)
target_include_directories(mylib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Demo
add_executable(demo example/demo.cpp)
target_link_libraries(demo PRIVATE mylib)

# Test
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

#Test Executable
enable_testing()
add_executable(tests test/test_stack.cpp)
target_link_libraries(tests PRIVATE mylib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)