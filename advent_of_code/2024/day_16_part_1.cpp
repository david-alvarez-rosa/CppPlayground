#include <climits>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
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
  auto inline RotateClockwise() noexcept -> void {
    std::swap(row, col);
    col *= -1;
  }
  auto inline RotateCounterClockwise() noexcept -> void {
    std::swap(row, col);
    row *= -1;
  }
  auto inline operator==(const Vector2D& other) const noexcept -> bool {
    return row == other.row && col == other.col;
  }
  friend auto inline operator+(Vector2D lhs, Vector2D rhs) noexcept -> Vector2D;
};

[[nodiscard]] auto inline operator+(Vector2D lhs, Vector2D rhs) noexcept
    -> Vector2D {
  lhs += rhs;
  return lhs;
};

using Pos = Vector2D;
using Dir = Vector2D;
using Node = std::pair<Pos, Dir>;  // (pos, dir)

struct NodeHash {  // Must define for hash set / hash map
  std::size_t operator()(const Node& node) const {
    const auto& [pos, dir] = node;
    return std::hash<int>{}(pos.row) ^ (std::hash<int>{}(pos.col) << 1) ^
           (std::hash<int>{}(dir.row) ^ (std::hash<int>{}(dir.col) << 1) << 1);
  }
};

class Maze final {
 public:
  explicit Maze(std::vector<std::vector<char>> maze) : maze_{maze} {}

  [[nodiscard]] auto ComputeScore() const noexcept -> int {
    auto lowest_score{INT_MAX};
    auto start_pos = FindStartPos();
    auto end_pos = FindEndPos();
    auto visited = std::unordered_set<Node, NodeHash>{};
    auto scores = std::unordered_map<Node, int, NodeHash>{};
    auto nodes = std::queue<Node>{};
    auto check_neighbour = [&nodes, &visited, &scores, this](
                               const Pos& pos, const Dir& dir,
                               int score) -> void {
      auto node = Node{pos, dir};
      if (IsInsideMaze(pos) && !IsWall(pos) &&
          (!visited.contains(node) || scores[node] > score)) {
        visited.insert(node);
        scores[node] = score;
        nodes.push(node);
      }
    };
    auto start_node = Node{start_pos, {0, 1}};
    nodes.emplace(start_node);
    visited.insert(start_node);
    scores[start_node] = 0;
    while (!nodes.empty()) {  // Dijkstra
      auto node = nodes.front();
      auto [pos, dir] = node;
      auto score = scores[node];
      nodes.pop();
      if (pos == end_pos) {
        lowest_score = std::min(lowest_score, score);
        continue;
      }

      // 1. No rotation
      check_neighbour(pos + dir, dir, score + 1);

      // 2. Clockwise rotation
      auto next_dir = dir;
      next_dir.RotateClockwise();
      check_neighbour(pos + next_dir, next_dir, score + 1001);

      // 3. Counter-clockwise rotation
      next_dir = dir;
      next_dir.RotateCounterClockwise();
      check_neighbour(pos + next_dir, next_dir, score + 1001);
    }

    return lowest_score;
  }

 private:
  std::vector<std::vector<char>> maze_;

  [[nodiscard]] auto FindEndPos() const noexcept -> Pos {
    for (auto i{0}; i < maze_.size(); ++i) {
      for (auto j{0}; j < maze_[0].size(); ++j) {
        if ('E' == maze_[i][j]) [[unlikely]] {
          return {i, j};
        }
      }
    }

    [[unlikely]] std::unreachable();
    return {-1, -1};
  }

  [[nodiscard]] auto FindStartPos() const noexcept -> Pos {
    for (auto i{0}; i < maze_.size(); ++i) {
      for (auto j{0}; j < maze_[0].size(); ++j) {
        if ('S' == maze_[i][j]) [[unlikely]] {
          return {i, j};
        }
      }
    }

    [[unlikely]] std::unreachable();
    return {-1, -1};
  }

  [[nodiscard]] inline auto IsWall(Pos pos) const noexcept -> bool {
    return '#' == maze_[pos.row][pos.col];
  }

  [[nodiscard]] inline auto IsInsideMaze(Pos pos) const noexcept -> bool {
    return pos.row >= 0 && pos.row < maze_.size() && pos.col >= 0 &&
           pos.col < maze_[0].size();
  }
};

auto ParseInputFile(const std::string& file_name) -> Maze {
  auto maze = std::vector<std::vector<char>>{};
  auto file_stream = std::ifstream{file_name};
  auto line = std::string{};
  while (file_stream >> line) {
    maze.emplace_back(line.begin(), line.end());
  }
  return Maze(maze);
}

auto main(int argc, char* argv[]) -> int {
  auto maze = ParseInputFile(argv[1]);
  std::cout << maze.ComputeScore() << "\n";
}
