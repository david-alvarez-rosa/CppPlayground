cmake_minimum_required(VERSION 3.10)
project(CppPlayground)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_CLANG_TIDY clang-tidy)
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -funroll-loops")

find_package(GTest REQUIRED)
add_executable(cpp_playground "main.cpp")
target_link_libraries(cpp_playground PRIVATE GTest::gtest_main GTest::gmock_main)

enable_testing()
gtest_discover_tests(cpp_playground)
