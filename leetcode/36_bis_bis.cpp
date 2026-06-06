#include <gtest/gtest.h>

#include <array>

using Board = std::vector<std::vector<char>>;

class Solution {
 public:
  [[nodiscard]]
  static auto isValidSudoku(const Board& board) noexcept -> bool {
    constexpr auto n = 9;

    auto rows = std::array<std::array<bool, n>, n>{};
    for (auto row_i = 0ZU; row_i < n; ++row_i) {
      for (auto col_i = 0ZU; col_i < n; ++col_i) {
        auto cell = board[row_i][col_i];
        if ('.' == cell) {
          continue;
        }
        auto cell_num = static_cast<std::size_t>(cell - '1');
        if (rows[row_i][cell_num]) {
          return false;
        }
        rows[row_i][cell_num] = true;
      }
    }

    auto cols = std::array<std::array<bool, n>, n>{};
    for (auto col_i = 0ZU; col_i < n; ++col_i) {
      for (auto row_i = 0ZU; row_i < n; ++row_i) {
        auto cell = board[row_i][col_i];
        if ('.' == cell) {
          continue;
        }
        auto cell_num = static_cast<std::size_t>(cell - '1');
        if (cols[col_i][cell_num]) {
          return false;
        }
        cols[col_i][cell_num] = true;
      }
    }

    auto boxes = std::array<std::array<bool, n>, n>{};
    auto box_id = 0ZU;
    for (auto row_i = 0ZU; row_i < n; row_i += 3) {
      for (auto col_i = 0ZU; col_i < n; col_i += 3) {
        for (auto i = 0ZU; i < n; ++i) {
          auto cell = board[row_i + (i % 3)][col_i + (i / 3)];
          if ('.' == cell) {
            continue;
          }
          auto cell_num = static_cast<std::size_t>(cell - '1');
          if (boxes[box_id][cell_num]) {
            return false;
          }
          boxes[box_id][cell_num] = true;
        }
        ++box_id;
      }
    }

    return true;
  }
};

TEST(Solution, Test1) {
  auto board = Board{{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
                     {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
                     {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
                     {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
                     {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
                     {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
                     {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
                     {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
                     {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};
  EXPECT_TRUE(Solution::isValidSudoku(board));
}

TEST(Solution, Test2) {
  auto board = Board{{'8', '3', '.', '.', '7', '.', '.', '.', '.'},
                     {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
                     {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
                     {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
                     {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
                     {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
                     {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
                     {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
                     {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};
  EXPECT_FALSE(Solution::isValidSudoku(board));
}
