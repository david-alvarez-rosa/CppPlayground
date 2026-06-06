#include <gtest/gtest.h>

class Solution {
 public:
  [[nodiscard]]
  static auto findClosest(int x, int y, int z) noexcept -> int {
    auto dx = std::abs(x - z);
    auto dy = std::abs(y - z);
    if (dx < dy) return 1;
    if (dy < dx) return 2;
    return 0;
  }
};

TEST(Solution, Test1) { EXPECT_EQ(Solution::findClosest(2, 7, 4), 1); }
TEST(Solution, Test2) { EXPECT_EQ(Solution::findClosest(2, 5, 6), 2); }
TEST(Solution, Test3) { EXPECT_EQ(Solution::findClosest(1, 5, 3), 0); }
