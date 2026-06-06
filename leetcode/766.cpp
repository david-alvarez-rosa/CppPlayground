#include <gtest/gtest.h>

#include <unordered_map>
#include <vector>

class Solution {
 public:
  bool isToeplitzMatrix(std::vector<std::vector<int>>& matrix) {
    std::unordered_map<int, int> diags;
    for (std::size_t i = 0; i < matrix.size(); ++i) {
      for (std::size_t j = 0; j < matrix[0].size(); ++j) {
        if (diags.contains(j - i) && diags[j - i] != matrix[i][j]) {
          return false;
        }
        diags[j - i] = matrix[i][j];
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
