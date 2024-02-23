cmake_minimum_required(VERSION 3.10)
project(CppLeetcode)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(GTest REQUIRED)
add_executable(cpp_leetcode "main.cpp")
target_link_libraries(cpp_leetcode PRIVATE GTest::gtest_main GTest::gmock_main)

enable_testing()
gtest_discover_tests(cpp_leetcode)
