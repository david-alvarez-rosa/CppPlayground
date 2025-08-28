#include <gtest/gtest.h>

#include <queue>
#include <vector>

using Matrix = std::vector<std::vector<int>>;

class Solution {
 public:
  [[nodiscard]] static auto sortMatrix(Matrix& grid) noexcept -> Matrix {
    auto n = grid.size();
    auto get_diag_id = [] [[nodiscard]] (auto row, auto col) noexcept {
      return row - col;
    };
    auto is_bottom = [] [[nodiscard]] (auto row, auto col) noexcept {
      return row >= col;
    };

    auto bottom_diags =
        std::unordered_map<std::size_t, std::priority_queue<int>>{};
    auto top_diags = std::unordered_map<
        std::size_t,
        std::priority_queue<int, std::vector<int>, std::greater<int>>>{};

    for (auto row = 0ZU; row < n; ++row) {
      for (auto col = 0ZU; col < n; ++col) {
        auto diag_id = get_diag_id(row, col);
        if (is_bottom(row, col)) {
          bottom_diags[diag_id].emplace(grid[row][col]);
        } else {
          top_diags[diag_id].emplace(grid[row][col]);
        }
      }
    }

    for (auto row = 0ZU; row < n; ++row) {
      for (auto col = 0ZU; col < n; ++col) {
        if (auto diag_id = get_diag_id(row, col); is_bottom(row, col)) {
          grid[row][col] = bottom_diags[diag_id].top();
          bottom_diags[diag_id].pop();
        } else {
          grid[row][col] = top_diags[diag_id].top();
          top_diags[diag_id].pop();
        }
      }
    }

    return grid;
  }
};

TEST(SolutionTest, Test1) {
  auto grid = Matrix{{1, 7, 3}, {9, 8, 2}, {4, 5, 6}};
  auto expected = Matrix{{8, 2, 3}, {9, 6, 7}, {4, 5, 1}};
  EXPECT_EQ(expected, Solution::sortMatrix(grid));
}

TEST(SolutionTest, Test2) {
  auto grid = Matrix{{0, 1}, {1, 2}};
  auto expected = Matrix{{2, 1}, {1, 0}};
  EXPECT_EQ(expected, Solution::sortMatrix(grid));
}
