#include <gtest/gtest.h>

#include <vector>

class Solution {
 public:
  static int minimumArea(std::vector<std::vector<int>>& grid) {
    auto m = grid.size(), n = grid[0].size();

    auto min_row = [&]() -> int {
      for (auto row = 0U; row < m; ++row)
        for (auto col = 0U; col < n; ++col)
          if (1 == grid[row][col]) return row;
      return -1;
    }();
    auto max_row = [&]() -> int {
      for (auto row = m - 1; row >= 0; --row)
        for (auto col = 0U; col < n; ++col)
          if (1 == grid[row][col]) return row;
      return -1;
    }();
    auto min_col = [&]() -> int {
      for (auto col = 0U; col < n; ++col)
        for (auto row = 0U; row < m; ++row)
          if (1 == grid[row][col]) return col;
      return -1;
    }();
    auto max_col = [&]() -> int {
      for (auto col = n - 1; col >= 0; --col)
        for (auto row = 0U; row < m; ++row)
          if (1 == grid[row][col]) return col;
      return -1;
    }();

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
