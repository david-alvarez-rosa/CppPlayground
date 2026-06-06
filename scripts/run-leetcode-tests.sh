#!/usr/bin/env sh

set -e

cp scratch/test.cpp scratch/test.cpp.backup

[ -f build/debug/conan_toolchain.cmake ] || conan install . -of build/debug --build=missing -s build_type=Debug
cmake --preset debug

git diff --name-only HEAD~9 HEAD | grep -E "leetcode/.*cpp" | while read -r file_path
do
    [ -f "$file_path" ] || continue
    printf "\n-------- Running tests for file %s --------\n" "$file_path"
    cp "$file_path" scratch/test.cpp
    cmake --build --preset debug --target tests
    ctest --preset debug --output-on-failure && printf "Test succeeded :)\n\n" || exit 1
done

mv scratch/test.cpp.backup scratch/test.cpp
