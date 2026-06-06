#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using AntennaMap = std::vector<std::vector<char>>;

struct Pos {
  int row;
  int col;
  friend auto __attribute__((always_inline)) inline operator+(Pos lhs,
                                                              Pos rhs) noexcept
      -> Pos;
  friend auto __attribute__((always_inline)) inline operator-(Pos lhs,
                                                              Pos rhs) noexcept
      -> Pos;
  friend auto __attribute__((always_inline)) inline operator<<(
      std::ostream& /* out_stream */, Pos /* pos */) noexcept -> std::ostream&;
};

[[nodiscard]] auto __attribute__((always_inline)) inline operator+(
    Pos lhs, Pos rhs) noexcept -> Pos {
  return {.row = lhs.row + rhs.row, .col = lhs.col + rhs.col};
};

[[nodiscard]] auto __attribute__((always_inline)) inline operator-(
    Pos lhs, Pos rhs) noexcept -> Pos {
  return {.row = lhs.row - rhs.row, .col = lhs.col - rhs.col};
};

auto __attribute__((always_inline)) inline operator<<(std::ostream& out_stream,
                                                      Pos pos) noexcept
    -> std::ostream& {
  return out_stream << pos.row << ',' << pos.col;
}

auto CountUniqueAntinodes(AntennaMap& antenna_map) -> int {
  auto is_antenna = [](const char point) -> bool {
    return (point >= 'a' && point <= 'z') || (point >= 'A' && point <= 'Z') ||
           (point >= '0' && point <= '9');
  };
  auto is_inside_map = [&antenna_map](Pos pos) -> bool {
    return pos.row >= 0 && pos.row < antenna_map.size() && pos.col >= 0 &&
           pos.col < antenna_map[0].size();
  };

  auto antennas =
      std::unordered_map<char, std::vector<Pos>>{};  // (freq, positions)

  for (auto row{0}; row < antenna_map.size(); ++row) {
    for (auto col{0}; col < antenna_map[0].size(); ++col) {
      auto point = antenna_map[row][col];
      if (is_antenna(point)) {
        antennas[point].push_back({.row = row, .col = col});
      }
    }
  }

  for (const auto& [_, positions] : antennas) {
    for (auto i{0U}; i < positions.size(); ++i) {
      for (auto j{0}; j < positions.size(); ++j) {
        if (i == j) [[__unlikely__]] {
          continue;
        }
        auto antinode = positions[i] + positions[i] - positions[j];
        if (is_inside_map(antinode)) {
          antenna_map[antinode.row][antinode.col] = '#';
        }
      }
    }
  }

  auto num_antinodes{0};
  for (const auto& row : antenna_map) {
    for (const auto point : row) {
      if ('#' == point) {
        ++num_antinodes;
      }
    }
  }

  return num_antinodes;
}

auto ParseInputFile(const std::string& file_name) -> AntennaMap {
  auto antenna_map = AntennaMap{};
  auto file_stream = std::ifstream{file_name};
  auto line = std::string{};

  while (file_stream >> line) {
    antenna_map.emplace_back(line.begin(), line.end());
  }

  return antenna_map;
}

auto main(int argc, char* argv[]) -> int {
  auto antenna_map = ParseInputFile(argv[1]);
  std::cout << CountUniqueAntinodes(antenna_map) << "\n";
}
