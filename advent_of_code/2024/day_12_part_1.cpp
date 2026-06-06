#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_set>
#include <vector>

using Map = std::vector<std::vector<char>>;

struct Pos {
  int row;
  int col;
  friend auto __attribute__((always_inline)) inline operator+(Pos lhs,
                                                              Pos rhs) noexcept
      -> Pos;
  auto __attribute__((always_inline)) inline operator==(
      Pos other) const noexcept -> bool {
    return row == other.row && col == other.col;
  }
};

[[nodiscard]] auto __attribute__((always_inline)) inline operator+(
    Pos lhs, Pos rhs) noexcept -> Pos {
  return {.row = lhs.row + rhs.row, .col = lhs.col + rhs.col};
};

namespace std {
template <>
struct hash<Pos> {  // Must define hash func
  size_t operator()(const Pos& p) const {
    return hash<int>()(p.row) ^ (hash<int>()(p.col) << 1);
  }
};
}  // namespace std

auto ComputePrice(const Map& map) -> int {
  auto price{0};
  auto visited = std::unordered_set<Pos>{};
  auto directions = std::vector<Pos>{
      {0, 1},
      {0, -1},
      {1, 0},
      {-1, 0},
  };
  auto is_inside_map = [&map](Pos pos) -> bool {
    return pos.row >= 0 && pos.row < map.size() && pos.col >= 0 &&
           pos.col < map[0].size();
  };
  auto get_perimeter = [&map, &is_inside_map, &directions](Pos pos) -> int {
    auto perimeter{0};
    auto type = map[pos.row][pos.col];
    for (auto direction : directions) {
      auto new_pos = pos + direction;
      if (!is_inside_map(new_pos) || map[new_pos.row][new_pos.col] != type) {
        ++perimeter;
      }
    }
    return perimeter;
  };

  for (auto row{0}; row < map.size(); ++row) {
    for (auto col{0}; col < map[0].size(); ++col) {
      if (visited.contains({row, col})) {
        continue;
      }

      auto type = map[row][col];
      auto area{0};
      auto perimeter{0};

      auto q = std::queue<Pos>{};
      q.emplace(row, col);
      visited.emplace(row, col);
      while (!q.empty()) {
        auto pos = q.front();
        q.pop();
        ++area;
        perimeter += get_perimeter(pos);
        for (auto direction : directions) {
          auto new_pos = pos + direction;
          if (is_inside_map(new_pos) && !visited.contains(new_pos) &&
              type == map[new_pos.row][new_pos.col]) {
            q.push(new_pos);
            visited.insert(new_pos);
          }
        }
      }

      price += area * perimeter;
    }
  }

  return price;
}

auto ParseInputFile(const std::string& file_name) -> Map {
  auto map = std::vector<std::vector<char>>{};
  auto file_stream = std::ifstream{file_name};
  auto row = std::string{};

  while (file_stream >> row) {
    map.emplace_back(row.begin(), row.end());
  }

  return map;
}

auto main(int argc, char* argv[]) -> int {
  auto map = ParseInputFile(argv[1]);
  std::cout << ComputePrice(map) << "\n";
}
