#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

class Map {
 public:
  explicit Map(std::vector<std::vector<char>> map) : map_{std::move(map)} {}

  using Pos = std::pair<int, int>;

  auto GetGuardPosition() const noexcept -> Pos {
    for (auto row{0U}; row < map_.size(); ++row) {
      for (auto col{0U}; col < map_[0].size(); ++col) {
        if ('^' == map_[row][col]) {
          return {row, col};
        }
      }
    }

    std::unreachable();

    return {};
  }

  auto CountGuardPositions() -> int {
    auto [guard_row, guard_col] = GetGuardPosition();

    while (IsInsideMap({guard_row, guard_col})) {
      switch (map_[guard_row][guard_col]) {
        case '^': {
          if (guard_row - 1 >= 0 && '#' == map_[guard_row - 1][guard_col]) {
            map_[guard_row][guard_col] = '>';
          } else {
            map_[guard_row][guard_col] = 'X';
            --guard_row;
            if (guard_row >= 0) {
              map_[guard_row][guard_col] = '^';
            }
          }
          break;
        }
        case 'v': {
          if (guard_row + 1 < map_.size() &&
              '#' == map_[guard_row + 1][guard_col]) {
            map_[guard_row][guard_col] = '<';
          } else {
            map_[guard_row][guard_col] = 'X';
            ++guard_row;
            if (guard_row < map_.size()) {
              map_[guard_row][guard_col] = 'v';
            }
          }
          break;
        }
        case '<': {
          if (guard_col - 1 >= 0 && '#' == map_[guard_row][guard_col - 1]) {
            map_[guard_row][guard_col] = '^';
          } else {
            map_[guard_row][guard_col] = 'X';
            --guard_col;
            if (guard_col >= 0) {
              map_[guard_row][guard_col] = '<';
            }
          }
          break;
        }
        case '>': {
          if (guard_col + 1 < map_[0].size() &&
              '#' == map_[guard_row][guard_col + 1]) {
            map_[guard_row][guard_col] = 'v';
          } else {
            map_[guard_row][guard_col] = 'X';
            ++guard_col;
            if (guard_col < map_[0].size()) {
              map_[guard_row][guard_col] = '>';
            }
          }
          break;
        }

        default:
          std::unreachable();
          break;
      }
    }

    auto count{0};
    for (auto row{0U}; row < map_.size(); ++row) {
      for (auto col{0U}; col < map_[0].size(); ++col) {
        if ('X' == map_[row][col]) {
          ++count;
        }
      }
    }

    return count;
  }

 private:
  std::vector<std::vector<char>> map_;

  __attribute__((always_inline)) inline auto IsInsideMap(Pos pos) const noexcept
      -> bool {
    return pos.first < map_.size() && pos.second < map_[0].size();
  }
};

auto ParseInputFile(const std::string& file_name) -> Map {
  auto raw_map = std::vector<std::vector<char>>{};
  auto file_stream = std::ifstream{file_name};
  auto line = std::string{};

  while (file_stream >> line) {
    raw_map.emplace_back(line.begin(), line.end());
  }

  return Map{raw_map};
}

auto main(int argc, char* argv[]) -> int {
  auto map = ParseInputFile(argv[1]);
  std::cout << map.CountGuardPositions() << "\n";
}
