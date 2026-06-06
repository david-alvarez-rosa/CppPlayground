#include <chrono>
#include <fstream>
#include <iostream>
#include <ostream>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class Map final {
 public:
  explicit Map(std::vector<std::vector<char>> map) : map_{std::move(map)} {}

  struct Pos {
    int row;
    int col;
    Pos(int row, int col) noexcept : row{row}, col{col} {}
    auto inline operator+=(const Pos& other) noexcept -> Pos& {
      row += other.row;
      col += other.col;
      return *this;
    }
    friend auto inline operator+(Pos lhs, const Pos& rhs) noexcept -> Pos;
    [[__nodiscard__]] auto inline operator<(const Pos& other) const noexcept
        -> bool {
      if (row == other.row) {
        return col < other.col;
      }
      return row < other.row;
    }
  };

  friend auto operator<<(std::ostream& /* out_stream */,
                         const Map& /* map */) noexcept -> std::ostream&;

  [[__nodiscard__]] auto GetGuardPosition() const noexcept -> Pos {
    for (auto row{0}; row < map_.size(); ++row) {
      for (auto col{0}; col < map_[0].size(); ++col) {
        if ('^' == map_[row][col]) [[__unlikely__]] {
          return {row, col};
        }
      }
    }

    [[__unlikely__]] std::unreachable();
    return {-1, -1};
  }

  auto CountLoopObstructions() noexcept -> int {
    auto count{0};
    auto guard_pos = GetGuardPosition();

    while (IsInsideMap(guard_pos)) {
      count += static_cast<int>(CanBeObstructedToLoop(guard_pos));

      auto& curr_cell = map_[guard_pos.row][guard_pos.col];
      auto next_guard_pos = guard_pos + directions_.at(curr_cell);

      if (!IsInsideMap(next_guard_pos)) [[__unlikely__]] {
        break;
      }

      auto& next_cell = map_[next_guard_pos.row][next_guard_pos.col];
      if ('#' == next_cell) {
        Turn(curr_cell);
      } else [[__likely__]] {
        guard_pos = next_guard_pos;
        next_cell = curr_cell;
      }
    }

    return count;
  }

 private:
  std::vector<std::vector<char>> map_;
  using Dir = Pos;
  std::unordered_map<char, Dir> directions_{
      {'^', {-1, 0}},
      {'>', {0, 1}},
      {'v', {1, 0}},
      {'<', {0, -1}},
  };
  std::unordered_map<char, char> turns_{
      {'^', '>'},
      {'>', 'v'},
      {'v', '<'},
      {'<', '^'},
  };
  mutable std::set<Pos> obstructions_;

  __attribute__((always_inline)) inline auto IsInsideMap(Pos pos) const noexcept
      -> bool {
    return pos.row < map_.size() && pos.col < map_[0].size();
  }

  __attribute__((always_inline)) inline auto Turn(char& cell) const noexcept
      -> void {  // No except mis cojones
    cell = turns_.at(cell);
  }

  [[__nodiscard__]] auto CanBeObstructedToLoop(Pos guard_pos) const noexcept
      -> bool {
    auto map_tmp = map_;  // Efficiency, yay!

    auto& curr_cell = map_tmp[guard_pos.row][guard_pos.col];
    const auto obstruction_pos = guard_pos + directions_.at(curr_cell);

    if (!IsInsideMap(obstruction_pos)) [[__unlikely__]] {
      return false;
    }

    auto& obstruction_cell = map_tmp[obstruction_pos.row][obstruction_pos.col];
    if ('#' == obstruction_cell) [[__unlikely__]] {
      return false;
    }
    obstruction_cell = '#';

    auto visited = std::set<std::pair<Pos, char>>{};
    while (IsInsideMap(guard_pos)) {
      auto& curr_cell = map_tmp[guard_pos.row][guard_pos.col];

      if (visited.contains({guard_pos, curr_cell})) {
        if (!obstructions_.contains(obstruction_pos)) {
          obstructions_.insert(obstruction_pos);
          return true;
        }
        return false;
      }
      visited.insert({guard_pos, curr_cell});

      auto next_guard_pos = guard_pos + directions_.at(curr_cell);
      if (!IsInsideMap(next_guard_pos)) [[__unlikely__]] {
        break;
      }

      auto& next_cell = map_tmp[next_guard_pos.row][next_guard_pos.col];
      if ('#' == next_cell) {
        Turn(curr_cell);
      } else [[__likely__]] {
        guard_pos = next_guard_pos;
        next_cell = curr_cell;
      }
    }

    return false;
  }
};

auto operator<<(std::ostream& out_stream, const Map& map) noexcept
    -> std::ostream& {
  for (const auto& row : map.map_) {
    for (const auto cell : row) {
      out_stream << cell;
    }
    out_stream << "\n";
  }
  return out_stream;
}

[[nodiscard]] auto inline operator+(Map::Pos lhs, const Map::Pos& rhs) noexcept
    -> Map::Pos {
  lhs += rhs;
  return lhs;
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

class Timer final {
 public:
  explicit Timer(int iterations) noexcept
      : iterations_{iterations},
        start_time_{std::chrono::high_resolution_clock::now()} {}

  // Rule of 5 - not intended to be copied / moved
  Timer(const Timer& other) = delete;
  Timer(Timer&& other) = delete;
  auto operator=(const Timer& other) noexcept -> Timer& = delete;
  auto operator=(Timer&& other) noexcept -> Timer& = delete;

  ~Timer() noexcept {
    auto end_time = std::chrono::high_resolution_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>(
        end_time - start_time_);
    std::cout << "Elapsed time: " << elapsed_time.count() / iterations_ << "\n";
  }

 private:
  int iterations_;
  std::chrono::time_point<std::chrono::high_resolution_clock>
      start_time_;  // Must be last
};

// Redundant checks, because why not lol
static_assert(!std::is_copy_constructible<Timer>::value);
static_assert(!std::is_copy_assignable<Timer>::value);
static_assert(!std::is_move_constructible<Timer>::value);
static_assert(!std::is_move_assignable<Timer>::value);

auto main(int argc, char* argv[]) -> int {
  auto map = ParseInputFile(argv[1]);

  constexpr const static auto iterations{1};
  {
    auto timer = Timer{iterations};
    for (auto i{0U}; i < iterations; ++i) {
      auto map_tmp = map;  // It's unfortunate, but map is not const
      volatile auto ans = map_tmp.CountLoopObstructions();
      __asm__ volatile("" ::: "memory");
    }
  }

  std::cout << map.CountLoopObstructions() << "\n";
}
