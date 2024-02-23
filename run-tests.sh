#!/usr/bin/env sh

cp main.cpp main.cpp.backup

find . -name '*.cpp' -not -path './build/*' -mindepth 2 | while read -r file_path
do
    echo "Running tests for file $file_path"
    cp "$file_path" ./main.cpp
    cmake -DCMAKE_BUILD_TYPE=Release -B build
    cmake --build build
    ./build/cpp_leetcode || exit 1
done

mv main.cpp.backup main.cpp
