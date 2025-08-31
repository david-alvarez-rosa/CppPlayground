#include <gtest/gtest.h>

#include <cstddef>
#include <vector>

using Sudoku = std::vector<std::vector<char>>;

class Solution {
  static constexpr auto N = 9;

  bool isValid(const Sudoku& sudoku, std::size_t row, std::size_t col,
               char cell) {
    for (auto i = 0ZU; i < N; ++i)
      if (sudoku[row][i] == cell || sudoku[i][col] == cell ||
          sudoku[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3] == cell)
        return false;
    return true;
  }

 public:
  auto solveSudoku(Sudoku& sudoku) noexcept -> bool {
    for (auto row = 0ZU; row < N; ++row) {
      for (auto col = 0ZU; col < N; ++col) {
        if (sudoku[row][col] != '.') continue;
        for (auto c = '1'; c <= '9'; c++) {
          if (isValid(sudoku, row, col, c)) {
            sudoku[row][col] = c;
            if (solveSudoku(sudoku)) return true;
            sudoku[row][col] = '.';
          }
        }
        return false;
      }
    }
    return true;
  }
};

TEST(Solution, Test1) {
  auto sudoku = Sudoku{{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
                       {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
                       {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
                       {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
                       {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
                       {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
                       {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
                       {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
                       {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};
  auto solved_sudoku = Sudoku{{'5', '3', '4', '6', '7', '8', '9', '1', '2'},
                              {'6', '7', '2', '1', '9', '5', '3', '4', '8'},
                              {'1', '9', '8', '3', '4', '2', '5', '6', '7'},
                              {'8', '5', '9', '7', '6', '1', '4', '2', '3'},
                              {'4', '2', '6', '8', '5', '3', '7', '9', '1'},
                              {'7', '1', '3', '9', '2', '4', '8', '5', '6'},
                              {'9', '6', '1', '5', '3', '7', '2', '8', '4'},
                              {'2', '8', '7', '4', '1', '9', '6', '3', '5'},
                              {'3', '4', '5', '2', '8', '6', '1', '7', '9'}};
  Solution{}.solveSudoku(sudoku);
  EXPECT_EQ(solved_sudoku, sudoku);
}
