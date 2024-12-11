#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
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

auto NumberOfStones(std::vector<int64_t> stones, int iterations) -> int {
  while (iterations--) {
    auto new_stones = std::vector<int64_t>{};
    for (auto stone : stones) {
      if (0 == stone) {
        new_stones.push_back(1);
      } else if (NumberOfDigits(stone) % 2 == 0) {
        auto [left, right] = SplitNumber(stone);
        new_stones.push_back(left);
        new_stones.push_back(right);
      } else {
        new_stones.push_back(2024 * stone);
      }
    }
    stones = new_stones;
  }

  return stones.size();
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
  std::cout << NumberOfStones(stones, 25) << std::endl;
}
