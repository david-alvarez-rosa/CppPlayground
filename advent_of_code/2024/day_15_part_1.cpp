#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

struct Pos {
  int row;
  int col;
  auto inline operator+=(const Pos& other) noexcept -> Pos& {
    row += other.row;
    col += other.col;
    return *this;
  }
  friend auto inline operator+(Pos lhs, Pos rhs) noexcept -> Pos;
};

[[nodiscard]] auto inline operator+(Pos lhs, Pos rhs) noexcept -> Pos {
  lhs += rhs;
  return lhs;
};

using Dir = Pos;

class Warehouse final {
 public:
  explicit Warehouse(std::vector<std::vector<char>> map,
                     std::vector<Dir> moves) noexcept
      : map_{std::move(map)}, moves_{std::move(moves)} {
    robot_pos_ = FindRobotPos();
  }

  auto Iterate() noexcept -> void {
    for (auto move : moves_) {
      if (Move(robot_pos_, move)) {
        robot_pos_ += move;
      }
    }
  }

  auto Move(Pos pos, Pos dir) -> bool {
    auto next_pos = pos + dir;
    if (!IsInsideMap(next_pos) || IsWall(next_pos)) {
      return false;
    }

    if (IsEmpty(next_pos) || Move(next_pos, dir)) {
      std::swap(map_[pos.row][pos.col], map_[next_pos.row][next_pos.col]);
      return true;
    }

    return false;
  }

  auto ComputeBoxCoordinatesSum() const noexcept -> int {
    auto sum{0};

    for (auto i{0}; i < map_.size(); ++i) {
      for (auto j{0}; j < map_[0].size(); ++j) {
        if (IsBox({i, j})) {
          sum += (i * 100 + j);
        }
      }
    }

    return sum;
  }

 private:
  std::vector<std::vector<char>> map_;
  std::vector<Dir> moves_;
  Pos robot_pos_;

  [[nodiscard]] auto FindRobotPos() const noexcept -> Pos {
    for (auto row{0}; row < map_.size(); ++row) {
      for (auto col{0}; col < map_[0].size(); ++col) {
        if ('@' == map_[row][col]) [[unlikely]] {
          return {row, col};
        }
      }
    }

    [[unlikely]] std::unreachable();
    return {-1, -1};
  }

  [[nodiscard]] inline auto IsInsideMap(Pos pos) const noexcept -> bool {
    return pos.row >= 0 && pos.row < map_.size() && pos.col >= 0 &&
           pos.col < map_[0].size();
  }

  [[nodiscard]] inline auto IsEmpty(Pos pos) const noexcept -> bool {
    return '.' == map_[pos.row][pos.col];
  }

  [[nodiscard]] inline auto IsWall(Pos pos) const noexcept -> bool {
    return '#' == map_[pos.row][pos.col];
  }

  [[nodiscard]] inline auto IsBox(Pos pos) const noexcept -> bool {
    return 'O' == map_[pos.row][pos.col];
  }
};

[[nodiscard]] auto ParseInputFile(const std::string& file_name) -> Warehouse {
  auto map = std::vector<std::vector<char>>{};
  auto moves = std::vector<Dir>{};
  auto first_part{true};
  auto file_stream = std::ifstream{file_name};
  auto line = std::string{};

  while (std::getline(file_stream, line)) {
    if (line.empty()) {
      first_part = false;
      continue;
    }

    if (first_part) {
      map.emplace_back(line.begin(), line.end());
    } else {
      for (auto raw_move : line) {
        auto move = Pos{};
        switch (raw_move) {
          case '>': {
            move = Pos{0, 1};
            break;
          }
          case 'v': {
            move = Pos{1, 0};
            break;
          }
          case '<': {
            move = Pos{0, -1};
            break;
          }
          case '^': {
            move = Pos{-1, 0};
            break;
          }
          default: {
            [[unlikely]] std::unreachable();
            break;
          }
        }
        moves.push_back(move);
      }
    }
  }

  return Warehouse{map, moves};
}

auto main(int argc, char* argv[]) -> int {
  auto warehouse = ParseInputFile(argv[1]);
  warehouse.Iterate();
  std::cout << warehouse.ComputeBoxCoordinatesSum() << "\n";
}
