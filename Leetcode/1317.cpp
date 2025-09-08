#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <vector>

class Solution {
 public:
  [[nodiscard]]
  static auto getNoZeroIntegers(int n) noexcept -> std::vector<int> {
    auto x = 0, y = 0, mult = 1;

    while (n) {
      auto digit = n % 10;

      if (digit == 1) {
        if (n / 10) {
          x += mult * 2;
          y += mult * 9;
          n -= 10;
        } else {
          y += mult * 1;
        }
      } else if (digit == 0) {
        x += mult * 1;
        y += mult * 9;
        n -= 10;
      } else {
        x += mult * 1;
        y += mult * (digit - 1);
      }

      mult *= 10;
      n /= 10;
    }

    return {x, y};
  }
};

/**

83392 easy unless 0 or 1

1345
09
0

8513
xx

8203
x15
x15

1803
09
09

19
 1
 8

**/

TEST(SolutionTest, Test1) {
  EXPECT_THAT(Solution::getNoZeroIntegers(2), testing::ElementsAre(1, 1));
}

TEST(SolutionTest, Test2) {
  EXPECT_THAT(Solution::getNoZeroIntegers(11), testing::ElementsAre(2, 9));
}

TEST(SolutionTest, Test3) {
  EXPECT_THAT(Solution::getNoZeroIntegers(108), testing::ElementsAre(11, 97));
}

TEST(SolutionTest, Test175) {
  EXPECT_THAT(Solution::getNoZeroIntegers(19), testing::ElementsAre(1, 18));
}
