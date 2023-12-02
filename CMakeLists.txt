cmake_minimum_required(VERSION 3.10)
project(CppPlayground)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# set(CMAKE_CXX_CLANG_TIDY clang-tidy)

add_executable(cpp_playground "main.cpp")
