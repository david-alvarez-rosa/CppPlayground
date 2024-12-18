#include <climits>
#include <fstream>
#include <functional>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

struct Vector2D {
  int row;
  int col;
  auto inline operator+=(const Vector2D& other) noexcept -> Vector2D& {
    row += other.row;
    col += other.col;
    return *this;
  }
  auto inline operator==(const Vector2D& other) const noexcept -> bool {
    return row == other.row && col == other.col;
  }
  auto inline operator<(const Vector2D& other) const noexcept -> bool {
    if (row == other.row) {
      return col < other.col;
    }
    return row < other.row;
  }
  friend auto inline operator+(Vector2D lhs, Vector2D rhs) noexcept -> Vector2D;
};

[[nodiscard]] auto inline operator+(Vector2D lhs,
                                    Vector2D rhs) noexcept -> Vector2D {
  lhs += rhs;
  return lhs;
};

using Pos = Vector2D;
using Dir = Vector2D;

namespace std {
template <>
struct hash<Vector2D> {
  size_t operator()(const Vector2D& v) const {
    return hash<int>()(v.row) ^ (hash<int>()(v.col) << 1);
  }
};
}  // namespace std

class MemorySpace final {
 public:
  explicit MemorySpace(std::vector<Pos> byte_positions) noexcept {
    for (auto i{0}; i < 1024; i++) {
      grid_[byte_positions[i].row][byte_positions[i].col] = '#';
    }
  }

  auto CountSteps() const noexcept -> int {
    auto lengths = std::unordered_map<Pos, int>{};
    auto pq = std::priority_queue<std::pair<int, Pos>,
                                  std::vector<std::pair<int, Pos>>,
                                  std::greater<>>{};  // (length, pos)
    lengths[Pos{0, 0}] = 0;
    pq.emplace(0, Pos{0, 0});

    while (!pq.empty()) {  // dijkstra
      auto [length, pos] = pq.top();
      pq.pop();

      if (Pos{70, 70} == pos) {
        return length;
      }

      for (auto dir : dirs_) {
        auto next_pos = pos + dir;
        if (IsInsideGrid(next_pos) && !IsWall(next_pos) &&
            (!lengths.contains(next_pos) || length + 1 < lengths[next_pos])) {
          lengths[next_pos] = length + 1;
          pq.emplace(length + 1, next_pos);
        }
      }
    }
    return -1;
  }

 private:
  std::vector<std::vector<char>> grid_ =
      std::vector<std::vector<char>>(71, std::vector<char>(71, '.'));
  std::vector<Dir> dirs_{
      {0, 1},
      {0, -1},
      {1, 0},
      {-1, 0},
  };

  [[nodiscard]] auto inline IsInsideGrid(Pos pos) const noexcept -> bool {
    return pos.row >= 0 && pos.row < grid_.size() && pos.col >= 0 &&
           pos.col < grid_[0].size();
  }

  [[nodiscard]] auto inline IsWall(Pos pos) const noexcept -> bool {
    return '#' == grid_[pos.row][pos.col];
  }
};

auto ParseInputFile(const std::string& file_name) -> std::vector<Pos> {
  auto positions = std::vector<Pos>{};
  auto file_stream = std::ifstream{file_name};
  char tmp;
  auto pos = Pos{};
  while (file_stream >> pos.col >> tmp >> pos.row) {
    positions.push_back(pos);
  }
  return positions;
}

auto main(int argc, char* argv[]) -> int {
  auto positions = ParseInputFile(argv[1]);
  auto memory_space = MemorySpace{positions};
  std::cout << memory_space.CountSteps() << std::endl;
}
