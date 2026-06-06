#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

__attribute__((always_inline)) inline auto NumberOfDigits(int64_t num)
    -> int64_t {
  return std::to_string(num).length();
}

__attribute__((always_inline)) inline auto SplitNumber(int64_t num)
    -> std::pair<int64_t, int64_t> {
  auto tmp = std::to_string(num);
  auto left = tmp.substr(0, tmp.length() / 2);
  auto right = tmp.substr(tmp.length() / 2);

  return {std::stoi(left), std::stoi(right)};
}

auto NumberOfStones(const std::vector<int64_t>& stones, int iterations)
    -> int64_t {
  auto stone_fqs = std::unordered_map<int64_t, int64_t>{};  // (stone, fq)

  for (auto stone : stones) {
    stone_fqs[stone]++;
  }

  while (iterations--) {
    auto new_stone_fqs = std::unordered_map<int64_t, int64_t>{};

    for (auto [stone, fq] : stone_fqs) {
      if (0 == stone) {
        new_stone_fqs[1] += stone_fqs[0];
      } else if (NumberOfDigits(stone) % 2 == 0) {
        auto [left, right] = SplitNumber(stone);
        new_stone_fqs[left] += stone_fqs[stone];
        new_stone_fqs[right] += stone_fqs[stone];
      } else {
        new_stone_fqs[stone * 2024] += stone_fqs[stone];
      }
    }
    stone_fqs = new_stone_fqs;
  }

  auto num_stones{0LL};
  for (const auto [_, fq] : stone_fqs) {
    num_stones += fq;
  }

  return num_stones;
}

auto ParseInputFile(const std::string& file_name) -> std::vector<int64_t> {
  auto stones = std::vector<int64_t>{};
  auto file_stream = std::ifstream{file_name};
  auto stone{0};
  while (file_stream >> stone) {
    stones.push_back(stone);
  }
  return stones;
}

auto main(int argc, char* argv[]) -> int {
  auto stones = ParseInputFile(argv[1]);
  std::cout << NumberOfStones(stones, 75) << std::endl;
}
