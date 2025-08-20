#include <gtest/gtest.h>

#include <vector>

class Solution {
  int countSquaresWithStart(const std::vector<std::vector<int>>& matrix,
                            std::size_t row_start, std::size_t col_start) {
    if (0 == matrix[row_start][col_start]) {
      return 0;
    }
    auto ans = 0;
    for (std::size_t size = 1; row_start + size - 1 < matrix.size() &&
                               col_start + size - 1 < matrix[0].size();
         ++size) {
      for (std::size_t row = row_start; row < row_start + size; ++row) {
        for (std::size_t col = col_start; col < col_start + size; ++col) {
          if (0 == matrix[row][col]) {
            return ans;
          }
        }
      }
      ans += 1;
    }

    return ans;
  }

 public:
  int countSquares(const std::vector<std::vector<int>>& matrix) {
    auto ans = 0;

    for (std::size_t row_start = 0; row_start < matrix.size(); ++row_start) {
      for (std::size_t col_start = 0; col_start < matrix[0].size();
           ++col_start) {
        ans += countSquaresWithStart(matrix, row_start, col_start);
      }
    }

    return ans;
  }
};

TEST(SolutionTest, Test1) {
  std::vector<std::vector<int>> matrix{
      {0, 1, 1, 1}, {1, 1, 1, 1}, {0, 1, 1, 1}};
  EXPECT_EQ(15, Solution{}.countSquares(matrix));
}

TEST(SolutionTest, Test2) {
  std::vector<std::vector<int>> matrix{{1, 0, 1}, {1, 1, 0}, {1, 1, 0}};
  EXPECT_EQ(7, Solution{}.countSquares(matrix));
}
