#include <gtest/gtest.h>
#include <sys/cdefs.h>

#include <cstdint>

class Solution {
 public:
  [[nodiscard]] __attribute__((always_inline)) static auto flowerGame(
      int n, int m) noexcept -> int64_t {
    return static_cast<int64_t>(n) * m / 2;
  }
};

TEST(SolutionTest, Test1) { EXPECT_EQ(3, Solution::flowerGame(3, 2)); }

TEST(SolutionTest, Test2) { EXPECT_EQ(0, Solution::flowerGame(1, 1)); }
