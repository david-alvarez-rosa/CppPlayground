#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class GridWordCounter final {
 public:
  explicit GridWordCounter(std::vector<std::vector<char>> grid)
      : grid_{std::move(grid)} {}

  auto CountOcurrences() const noexcept -> int {
    auto count{0};

    for (auto row{0}; row < grid_.size() - 2; ++row) {
      for (auto col{0}; col < grid_[0].size() - 2; ++col) {
        count += static_cast<int>(IsXMas({row, col}));
      }
    }

    return count;
  }

 private:
  struct Pos {
    int row;
    int col;
    Pos(int row, int col) : row{row}, col{col} {}
  };

  std::vector<std::vector<char>> grid_;

  auto IsXMas(Pos&& start_pos) const noexcept -> bool {
    auto diag_a = std::string{grid_[start_pos.row][start_pos.col],
                              grid_[start_pos.row + 1][start_pos.col + 1],
                              grid_[start_pos.row + 2][start_pos.col + 2]};
    auto diag_b = std::string{grid_[start_pos.row][start_pos.col + 2],
                              grid_[start_pos.row + 1][start_pos.col + 1],
                              grid_[start_pos.row + 2][start_pos.col]};
    return (diag_a == "MAS" || diag_a == "SAM") &&
           (diag_b == "MAS" || diag_b == "SAM");
  }
};

auto ParseInputFile(const std::string& file_name) -> GridWordCounter {
  auto file_stream = std::ifstream{file_name};
  auto grid = std::vector<std::vector<char>>{};
  auto line = std::string{};

  while (file_stream >> line) {
    grid.emplace_back(line.begin(), line.end());
  }

  return GridWordCounter{grid};
}

auto main(int argc, char* argv[]) -> int {
  auto grid_word_counter = ParseInputFile(argv[1]);
  std::cout << grid_word_counter.CountOcurrences() << "\n";
}
