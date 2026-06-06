#include <gtest/gtest.h>

#include <vector>

class Solution {
 public:
  static int areaOfMaxDiagonal(std::vector<std::vector<int>>& dimensions) {
    auto max_diagonal{0}, max_area{0};

    for (const auto& dimension : dimensions) {
      auto curr_diagonal =
          dimension[0] * dimension[0] + dimension[1] * dimension[1];
      auto area = dimension[0] * dimension[1];

      if (curr_diagonal > max_diagonal ||
          (curr_diagonal == max_diagonal && area > max_area)) {
        max_diagonal = curr_diagonal;
        max_area = area;
      }
    }

    return max_area;
  }
};

TEST(SolutionTest, Test1) {
  std::vector<std::vector<int>> dimensions{{9, 3}, {8, 6}};
  EXPECT_EQ(48, Solution::areaOfMaxDiagonal(dimensions));
}

TEST(SolutionTest, Test2) {
  std::vector<std::vector<int>> dimensions{{3, 4}, {4, 3}};
  EXPECT_EQ(12, Solution::areaOfMaxDiagonal(dimensions));
}
