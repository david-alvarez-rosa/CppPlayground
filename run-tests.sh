#!/usr/bin/env sh

set -e

cp main.cpp main.cpp.backup

find . -name '*.cpp' -path './Leetcode/*' | while read -r file_path
do
    printf "\n-------- Running tests for file %s --------\n" "$file_path"
    cp "$file_path" ./main.cpp
    cmake -DCMAKE_BUILD_TYPE=Release -B build
    cmake --build build
    ./build/cpp_playground && printf "Test succeeded :)\n\n" || exit 1
done

mv main.cpp.backup main.cpp
