#include <gtest/gtest.h>

#include <vector>

class Solution {
 public:
  static int countSquares(std::vector<std::vector<int>>& matrix) {
    auto m = matrix.size();
    auto n = matrix[0].size();
    auto square_count = count(matrix[0].cbegin(), matrix[0].cend(), 1);

    for (std::size_t row = 1; row < m; row++) {
      square_count += matrix[row][0];
    }

    for (std::size_t row = 1; row < m; row++) {
      for (std::size_t col = 1; col < n; col++) {
        if (matrix[row][col] == 0) {
          continue;
        }

        matrix[row][col] = 1 + std::min(matrix[row - 1][col],
                                        std::min(matrix[row - 1][col - 1],
                                                 matrix[row][col - 1]));
        square_count += matrix[row][col];
      }
    }

    return square_count;
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
