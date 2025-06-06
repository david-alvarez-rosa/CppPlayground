cmake_minimum_required(VERSION 3.10)
project(CppPlayground)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_CLANG_TIDY clang-tidy)

add_executable(main "main.cpp")
target_compile_options(
  main
  PRIVATE -g
          -Wall
          -Wpedantic
          -Wextra
          -Wuninitialized
          -Wunused
          -Wshadow
          -Wconversion
          -fsanitize=address
          -fsanitize=undefined)
target_link_options(main PRIVATE -fsanitize=address -fsanitize=undefined)

add_executable(leetcode "leetcode.cpp")
find_package(GTest REQUIRED)
target_link_libraries(leetcode GTest::gtest_main GTest::gmock)
enable_testing()
gtest_discover_tests(leetcode)

add_executable(benchmark "benchmark.cpp")
find_package(benchmark REQUIRED)
target_compile_options(benchmark PRIVATE -O3)
target_link_libraries(benchmark PRIVATE benchmark::benchmark_main)

add_executable(assembly "assembly.cpp")
target_compile_options(
  assembly
  PRIVATE -save-temps
          -masm=intel
          -fverbose-asm
          -g0
          -O0
          -fno-asynchronous-unwind-tables
          -fno-ident
          -fno-addrsig
          -fno-exceptions
          -fno-rtti)
add_custom_command(
  TARGET assembly
  POST_BUILD
  COMMAND llvm-cxxfilt < ${CMAKE_BINARY_DIR}/assembly.s >
          ${CMAKE_BINARY_DIR}/assembly_demangled.s)
