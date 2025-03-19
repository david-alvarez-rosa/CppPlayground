#include <chrono>
#include <fstream>
#include <iostream>
#include <ostream>
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

  auto CountGuardPositions() -> int {
    auto guard_pos = GetGuardPosition();

    while (IsInsideMap(guard_pos)) {
      auto& curr_cell = map_[guard_pos.row][guard_pos.col];
      auto next_guard_pos = guard_pos + directions_.at(curr_cell);

      if (!IsInsideMap(next_guard_pos)) [[__unlikely__]] {
        curr_cell = 'X';
        break;
      }

      auto& next_cell = map_[next_guard_pos.row][next_guard_pos.col];
      if ('#' == next_cell) {
        Turn(curr_cell);
      } else [[__likely__]] {
        guard_pos = next_guard_pos;
        next_cell = curr_cell;
        curr_cell = 'X';
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

  __attribute__((always_inline)) inline auto IsInsideMap(Pos pos) const noexcept
      -> bool {
    return pos.row < map_.size() && pos.col < map_[0].size();
  }

  __attribute__((always_inline)) inline auto Turn(char& cell) const noexcept
      -> void {
    cell = turns_.at(cell);
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

  constexpr const static auto iterations{1000};
  {
    auto timer = Timer{iterations};
    for (auto i{0U}; i < iterations; ++i) {
      auto map_tmp = map;  // It's unfortunate, but map is not const
      volatile auto ans = map_tmp.CountGuardPositions();  // 269 mics with -03
      __asm__ volatile("" ::: "memory");
    }
  }

  std::cout << map.CountGuardPositions() << "\n";
}
