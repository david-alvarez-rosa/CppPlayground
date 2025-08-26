#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <vector>

class Solution {
 public:
  static std::vector<int> findDiagonalOrder(
      std::vector<std::vector<int>>& matrix) {
    auto m = matrix.size(), n = matrix[0].size(), row = 0ZU, col = 0ZU;
    auto ans = std::vector<int>{};
    ans.reserve(m * n);

    auto is_last = [&](std::size_t row, std::size_t col) noexcept -> bool {
      return row == m - 1 && col == n - 1;
    };
    auto is_upward = [&](std::size_t row, std::size_t col) noexcept -> bool {
      return (row + col) % 2 == 0;
    };

    while (!is_last(row, col)) {
      ans.push_back(matrix[row][col]);

      if (is_upward(row, col)) {
        if (col == n - 1)
          row++;
        else if (row == 0)
          col++;
        else {
          row--;
          col++;
        }
      } else {
        if (row == m - 1)
          col++;
        else if (col == 0)
          row++;
        else {
          row++;
          col--;
        }
      }
    }

    ans.push_back(matrix[row][col]);
    return ans;
  }
};

TEST(SolutionTest, Test1) {
  std::vector<std::vector<int>> matrix{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  EXPECT_THAT(Solution::findDiagonalOrder(matrix),
              testing::ElementsAreArray({1, 2, 4, 7, 5, 3, 6, 8, 9}));
}

TEST(SolutionTest, Test2) {
  std::vector<std::vector<int>> matrix{{1, 2}, {3, 4}};
  EXPECT_THAT(Solution::findDiagonalOrder(matrix),
              testing::ElementsAreArray({1, 2, 3, 4}));
}
