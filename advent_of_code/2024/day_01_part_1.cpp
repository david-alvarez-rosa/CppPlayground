#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <numeric>
#include <vector>

struct LocationIds {
  std::vector<int> left_ids;
  std::vector<int> right_ids;
};

auto ComputeDistance(LocationIds& location_ids) -> int {
  auto& left_ids = location_ids.left_ids;
  auto& right_ids = location_ids.right_ids;

  std::sort(left_ids.begin(), left_ids.end());
  std::sort(right_ids.begin(), right_ids.end());

  return std::transform_reduce(
      left_ids.cbegin(), left_ids.cend(), right_ids.cbegin(), 0, std::plus<>(),
      [](auto left, auto right) { return std::abs(left - right); });
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
  std::cout << ComputeDistance(location_ids) << "\n";
}
