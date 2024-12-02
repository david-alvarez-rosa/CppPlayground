#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

class Report final {
  std::vector<int> levels_;

 public:
  explicit Report(std::vector<int> levels) noexcept : levels_{levels} {}

  auto IsSafe() const noexcept -> bool {
    if (levels_.size() <= 1) return true;

    auto is_increasing = (levels_[1] - levels_[0]) > 0;

    for (size_t i{1}; i < levels_.size(); ++i) {
      auto delta = levels_[i] - levels_[i - 1];
      if (delta > 0 != is_increasing || std::abs(delta) < 1 ||
          std::abs(delta) > 3)
        return false;
    }

    return true;
  }
};

using Reports = std::vector<Report>;

auto ParseInputFile(const std::string& file_name) noexcept -> Reports {
  auto reports = Reports{};

  auto parse_line = [&reports](const auto& line) {
    auto levels = std::vector<int>{};
    auto level{0};
    auto line_stream = std::istringstream{line};
    while (line_stream >> level) levels.emplace_back(level);
    reports.emplace_back(levels);
  };

  std::ifstream file_stream{file_name};
  auto line = std::string{};
  while (std::getline(file_stream, line)) parse_line(line);

  return reports;
}

auto main(int argc, char* argv[]) -> int {
  auto reports = ParseInputFile(argv[1]);
  std::cout << std::accumulate(
      reports.cbegin(), reports.cend(), 0,
      [](int acc, const auto& report) { return acc + report.IsSafe(); });
}
