#!/usr/bin/env sh

set -e

cp main.cpp main.cpp.backup

export CC=clang
export CXX=clang++
cmake -S . -B build -G Ninja

find . -name '*.cpp' -path './Leetcode/*' | while read -r file_path
do
    printf "\n-------- Running tests for file %s --------\n" "$file_path"
    cp "$file_path" ./leetcode.cpp
    cmake --build build
    ./build/leetcode && printf "Test succeeded :)\n\n" || exit 1
done

mv main.cpp.backup main.cpp
