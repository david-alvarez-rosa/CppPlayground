#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class GridWordCounter final {
 public:
  GridWordCounter(std::vector<std::vector<char>> grid, std::string&& target)
      : grid_{std::move(grid)}, target_{target} {}

  auto CountOcurrences() const noexcept -> int {
    auto count{0};

    for (auto row{0}; row < grid_.size(); ++row) {
      for (auto col{0}; col < grid_[0].size(); ++col) {
        count += CountOcurrencesFrom({row, col});
      }
    }

    return count;
  }

 private:
  struct Pos {
    int row;
    int col;
    Pos(int row, int col) : row{row}, col{col} {}
    Pos& operator+=(const Pos& other) {
      row += other.row;
      col += other.col;
      return *this;
    }
  };

  std::vector<std::vector<char>> grid_;
  std::string target_;
  using Dir = Pos;
  std::vector<Dir> dirs_{{0, 1}, {0, -1}, {1, 0},  {-1, 0},
                         {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

  auto IsInsideGrid(const Pos& pos) const noexcept -> bool {
    return pos.row < grid_.size() && pos.col < grid_[0].size();
  }

  auto CountOcurrencesFrom(Pos&& start_pos) const noexcept -> int {
    if (target_[0] != grid_[start_pos.row][start_pos.col]) {
      return 0;
    }

    auto count{0};
    for (const auto& dir : dirs_) {
      auto pos = start_pos;
      for (auto i{1}; i < target_.length(); ++i) {
        pos += dir;
        if (!IsInsideGrid(pos) || grid_[pos.row][pos.col] != target_[i]) {
          break;
        }
        if (i == target_.length() - 1) {
          ++count;
        }
      }
    }
    return count;
  }
};

auto ParseInputFile(const std::string& file_name) -> GridWordCounter {
  auto file_stream = std::ifstream{file_name};
  auto grid = std::vector<std::vector<char>>{};
  auto line = std::string{};

  while (file_stream >> line) {
    grid.emplace_back(line.begin(), line.end());
  }

  return {grid, "XMAS"};
}

auto main(int argc, char* argv[]) -> int {
  auto grid_word_counter = ParseInputFile(argv[1]);
  std::cout << grid_word_counter.CountOcurrences() << "\n";
}
