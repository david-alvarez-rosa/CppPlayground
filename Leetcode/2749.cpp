#include <gtest/gtest.h>

#include <cstdint>

class Solution {
 public:
  [[nodiscard]]
  static auto makeTheIntegerZero(int64_t num1, int64_t num2) noexcept -> int {
    for (auto i = 1; i <= 60; ++i) {
      auto x = num1 - num2 * i;
      if (x < i) continue;

      auto count_one_bits = 0;
      while (x > 0) {
        count_one_bits += x & 1;
        x = x >> 1;
      }

      if (count_one_bits <= i) return i;
    }

    return -1;
  }
};

TEST(Solution, Test1) { EXPECT_EQ(Solution::makeTheIntegerZero(3, -2), 3); }
TEST(Solution, Test2) { EXPECT_EQ(Solution::makeTheIntegerZero(5, 7), -1); }
TEST(Solution, Test402) {
  EXPECT_EQ(Solution::makeTheIntegerZero(110, 55), -1);
}
