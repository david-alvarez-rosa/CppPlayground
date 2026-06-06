#include <gtest/gtest.h>

#include <unordered_set>

using Board = std::vector<std::vector<char>>;

class Solution {
 public:
  [[nodiscard]]
  static auto isValidSudoku(const Board& board) noexcept -> bool {
    constexpr auto n = 9;

    for (auto row_i = 0ZU; row_i < n; ++row_i) {
      auto row = std::unordered_set<char>{};
      for (auto col_i = 0ZU; col_i < n; ++col_i) {
        auto cell = board[row_i][col_i];
        if ('.' == cell) {
          continue;
        }
        if (row.contains(cell)) {
          return false;
        }
        row.insert(cell);
      }
    }

    for (auto col_i = 0ZU; col_i < n; ++col_i) {
      auto col = std::unordered_set<char>{};
      for (auto row_i = 0ZU; row_i < n; ++row_i) {
        auto cell = board[row_i][col_i];
        if ('.' == cell) {
          continue;
        }
        if (col.contains(cell)) {
          return false;
        }
        col.insert(cell);
      }
    }

    for (auto row_i = 0ZU; row_i < n; row_i += 3) {
      for (auto col_i = 0ZU; col_i < n; col_i += 3) {
        auto box = std::unordered_set<char>{};
        for (auto i = 0ZU; i < n; ++i) {
          auto cell = board[row_i + (i % 3)][col_i + (i / 3)];
          if ('.' == cell) {
            continue;
          }
          if (box.contains(cell)) {
            return false;
          }
          box.insert(cell);
        }
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
