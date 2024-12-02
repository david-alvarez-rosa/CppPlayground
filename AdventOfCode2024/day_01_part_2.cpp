#include <fstream>
#include <iostream>
#include <numeric>
#include <unordered_map>
#include <vector>

struct LocationIds {
  std::vector<int> left_ids;
  std::vector<int> right_ids;
};

auto ComputeSimilarity(const LocationIds& location_ids) -> int {
  auto right_fqs = std::unordered_map<int, int>{};
  for (const auto right_id : location_ids.right_ids) {
    right_fqs[right_id]++;
  }

  return std::accumulate(location_ids.left_ids.cbegin(),
                         location_ids.left_ids.cend(), 0,
                         [&right_fqs](int acc, const auto left_id) {
                           return acc + left_id * right_fqs[left_id];
                         });
}

auto ParseInputFile(const std::string& file_name) -> LocationIds {
  auto location_ids = LocationIds{};

  std::ifstream file_stream{file_name};
  auto left_id{0}, right_id{0};
  while (file_stream >> left_id >> right_id) {
    location_ids.left_ids.emplace_back(left_id);
    location_ids.right_ids.emplace_back(right_id);
  }

  return location_ids;
}

auto main(int argc, char* argv[]) -> int {
  auto location_ids = ParseInputFile(argv[1]);
  std::cout << ComputeSimilarity(location_ids) << "\n";
}
