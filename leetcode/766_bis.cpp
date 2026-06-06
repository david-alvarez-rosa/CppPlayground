#include <gtest/gtest.h>

#include <vector>

class Solution {
 public:
  bool isToeplitzMatrix(std::vector<std::vector<int>>& matrix) {
    auto is_inside = [&matrix](int i, int j) {
      return i >= 0 && i < matrix.size() && j >= 0 && j < matrix[0].size();
    };
    for (auto i = 0; i < matrix.size(); ++i) {
      for (auto j = 0; j < matrix[0].size(); ++j) {
        if (is_inside(i - 1, j - 1) && matrix[i - 1][j - 1] != matrix[i][j]) {
          return false;
        }
      }
    }
    return true;
  }
};

TEST(SolutionTest, Test1) {
  Solution solution;
  std::vector<std::vector<int>> matrix{
      {1, 2, 3, 4}, {5, 1, 2, 3}, {9, 5, 1, 2}};
  EXPECT_TRUE(solution.isToeplitzMatrix(matrix));
}

TEST(SolutionTest, Test2) {
  Solution solution;
  std::vector<std::vector<int>> matrix{{1, 2}, {2, 2}};
  EXPECT_FALSE(solution.isToeplitzMatrix(matrix));
}
