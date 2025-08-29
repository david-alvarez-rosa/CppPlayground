#!/usr/bin/env sh

set -e

cp test.cpp test.cpp.backup

export CC=clang
export CXX=clang++
cmake -S . -B build -G Ninja

git diff --name-only HEAD~9 HEAD | grep -E 'Leetcode/.*cpp' | while read -r file_path
do
    [ -f $file_path ] || continue
    printf "\n-------- Running tests for file %s --------\n" "$file_path"
    cp "$file_path" ./test.cpp
    cmake --build build
    ./build/test && printf "Test succeeded :)\n\n" || exit 1
done

mv test.cpp.backup test.cpp
