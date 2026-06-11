cmake_minimum_required(VERSION 3.25)
project(CppPlayground)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_program(CLANG_TIDY_PROGRAM clang-tidy)
if(CLANG_TIDY_PROGRAM)
  set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_PROGRAM}")
endif()

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
  set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
endif()

find_program(MOLD_PROGRAM mold)
if(MOLD_PROGRAM)
  add_link_options(-fuse-ld=mold)
endif()

add_executable(fast "scratch/fast.cpp")
set_target_properties(fast PROPERTIES CXX_CLANG_TIDY "")

add_executable(main "scratch/main.cpp")
target_compile_options(
  main
  PRIVATE
          -Wall
          -Wpedantic
          -Wextra
          -Wuninitialized
          -Wunused
          -Wunused-parameter
          -Wshadow
          -Wconversion
          -Wsign-conversion)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_compile_options(main PRIVATE -fsanitize=address -fsanitize=undefined)
  target_link_options(main PRIVATE -fsanitize=address -fsanitize=undefined)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
  target_compile_options(main PRIVATE -O3 -march=native -ffast-math)
endif()

add_executable(tests "scratch/test.cpp")
target_compile_options(
  tests
  PRIVATE -g
          -Wall
          -Wpedantic
          -Wextra
          -Wuninitialized
          -Wunused
          -Wunused-parameter
          -Wshadow
          -Wconversion
          -Wsign-conversion)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_compile_options(tests PRIVATE -fsanitize=address -fsanitize=undefined)
  target_link_options(tests PRIVATE -fsanitize=address -fsanitize=undefined)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
  target_compile_options(tests PRIVATE -O3 -Werror)
endif()

find_package(GTest REQUIRED)
include(GoogleTest)
enable_testing()
target_link_libraries(tests GTest::gtest_main GTest::gmock)
gtest_discover_tests(tests)

add_executable(benchmark "scratch/benchmark.cpp")
find_package(benchmark REQUIRED)
target_compile_options(benchmark PRIVATE -O3 -march=native -mtune=native -flto -ffast-math)
target_link_options(benchmark PRIVATE -flto)
target_link_libraries(benchmark PRIVATE benchmark::benchmark_main pthread)

add_executable(assembly "scratch/assembly.cpp")
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
  COMMAND
    llvm-cxxfilt < ${CMAKE_BINARY_DIR}/assembly.s >
    ${CMAKE_BINARY_DIR}/assembly_demangled.s && cat
    ${CMAKE_BINARY_DIR}/assembly_demangled.s)
