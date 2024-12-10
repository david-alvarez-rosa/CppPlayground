#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <unordered_set>
#include <vector>

struct Pos {
  int row;
  int col;
  friend auto __attribute__((always_inline)) inline operator+(
      Pos lhs, Pos rhs) noexcept -> Pos;
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

class TopographicMap final {
 public:
  explicit TopographicMap(std::vector<std::vector<int>> raw_map)
      : raw_map_{std::move(raw_map)} {}

  [[__nodiscard__]] auto SumTrailHeadScores() const noexcept -> int {
    auto sum{0};
    for (auto i{0}; i < raw_map_.size(); ++i) {
      for (auto j{0}; j < raw_map_[0].size(); ++j) {
        if (0 == raw_map_[i][j]) {
          sum += ComputeTrailHeadScore({i, j});
        }
      }
    }

    return sum;
  }

 private:
  std::vector<std::vector<int>> raw_map_;
  std::vector<std::vector<int>> adj_;
  std::vector<Pos> directions_{
      {0, 1},
      {0, -1},
      {1, 0},
      {-1, 0},
  };

  [[__nodiscard__]] auto ComputeTrailHeadScore(Pos head_pos) const noexcept
      -> int {
    auto count{0};
    auto visited = std::unordered_set<Pos>{};
    auto s = std::stack<Pos>{};
    s.push(head_pos);
    while (!s.empty()) {
      auto pos = s.top();
      s.pop();
      visited.insert(pos);
      auto height = raw_map_[pos.row][pos.col];
      if (9 == height) {
        ++count;
        continue;
      }

      for (auto direction : directions_) {
        auto adj_pos = pos + direction;
        if (IsInsideMap(adj_pos) &&
            raw_map_[adj_pos.row][adj_pos.col] == height + 1 &&
            !visited.contains(adj_pos)) {
          s.push(adj_pos);
        }
      }
    }

    return count;
  }

  [[__nodiscard__]] __attribute__((__always_inline__)) inline auto IsInsideMap(
      Pos pos) const noexcept -> bool {
    return pos.row >= 0 && pos.row < raw_map_.size() && pos.col >= 0 &&
           pos.col < raw_map_[0].size();
  }
};

auto ParseInputFile(const std::string& file_name) -> TopographicMap {
  auto topographic_map_raw = std::vector<std::vector<int>>{};
  auto file_stream = std::ifstream{file_name};
  auto line = std::string{};

  while (file_stream >> line) {
    auto row = std::vector<int>{};
    for (const auto digit_raw : line) {
      row.push_back(digit_raw - '0');
    }
    topographic_map_raw.push_back(row);
  }

  return TopographicMap{topographic_map_raw};
}

auto main(int argc, char* argv[]) -> int {
  auto topographic_map = ParseInputFile(argv[1]);
  std::cout << topographic_map.SumTrailHeadScores() << "\n";
}
