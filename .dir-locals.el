((nil . (
         (projectile-project-configure-cmd . "cmake -DCMAKE_BUILD_TYPE=Debug -B build")
         (projectile-project-compilation-cmd . "cmake --build build")
         ;; useful to use --gtest_filter=MySuite.MyTest
         (projectile-project-test-cmd . "cmake --build build && ./build/cpp_playground")
         (projectile-project-run-cmd . "./build/cpp_playground")
         (projectile-project-test-prefix . "test_"))))
