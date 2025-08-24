#include <gtest/gtest.h>

#include <vector>

class Solution {
 public:
  static int minimumArea(std::vector<std::vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();
    auto min_row = m, max_row = -1, min_col = n, max_col = -1;

    for (auto row = 0; row < m; row++) {
      for (auto col = 0; col < n; col++) {
        if (grid[row][col] == 1) {
          min_row = std::min(min_row, row);
          max_row = std::max(max_row, row);
          min_col = std::min(min_col, col);
          max_col = std::max(max_col, col);
        }
      }
    }

    return (max_row - min_row + 1) * (max_col - min_col + 1);
  }
};

TEST(SolutionTest, Test1) {
  std::vector<std::vector<int>> grid{{0, 1, 0}, {1, 0, 1}};
  EXPECT_EQ(6, Solution::minimumArea(grid));
}

TEST(SolutionTest, Test2) {
  std::vector<std::vector<int>> grid{{1, 0}, {0, 0}};
  EXPECT_EQ(1, Solution::minimumArea(grid));
}

TEST(SolutionTest, Test3) {
  std::vector<std::vector<int>> grid{{0, 1}};
  EXPECT_EQ(1, Solution::minimumArea(grid));
}
