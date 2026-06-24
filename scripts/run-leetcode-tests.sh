#!/usr/bin/env sh

set -e

export ASAN_OPTIONS=detect_leaks=0

profile="${CONAN_PROFILE:-conan/profile}"

cp scratch/tests.cpp scratch/tests.cpp.backup

[ -f build/debug/conan_toolchain.cmake ] || conan install . -of build/debug -pr "$profile" --build=missing --lockfile=conan.lock -s build_type=Debug
cmake --preset debug

git diff --name-only --diff-filter=AM HEAD~9 HEAD | grep -E "leetcode/.*cpp" | while read -r file_path
do
    [ -f "$file_path" ] || continue
    printf "\n-------- Running tests for file %s --------\n" "$file_path"
    cp "$file_path" scratch/tests.cpp
    cmake --build --preset debug --target tests
    ctest --preset debug --output-on-failure && printf "Test succeeded :)\n\n" || exit 1
done

mv scratch/tests.cpp.backup scratch/tests.cpp
