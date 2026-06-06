#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

class Report final {
 public:
  explicit Report(std::vector<int> levels) noexcept
      : levels_{std::move(levels)} {}

  auto IsSafe() const noexcept -> bool {
    // Lazy fuck

    for (auto i{0U}; i < levels_.size(); ++i) {
      auto tmp_levels = levels_;
      tmp_levels.erase(tmp_levels.begin() + i);
      if (IsSafePure(tmp_levels)) {
        return true;
      }
    }
    return false;
  }

 private:
  std::vector<int> levels_;

  static auto IsSafePure(const std::vector<int>& levels) noexcept -> bool {
    if (levels.size() <= 1) {
      return true;
    }

    auto is_increasing = (levels[1] - levels[0]) > 0;

    auto is_safe_pair = [is_increasing](const auto left, const auto right) {
      return is_increasing == right > left && std::abs(left - right) >= 1 &&
             std::abs(left - right) <= 3;
    };

    for (auto i{1U}; i < levels.size(); ++i) {
      if (!is_safe_pair(levels[i - 1], levels[i])) {
        return false;
      }
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
    while (line_stream >> level) {
      levels.emplace_back(level);
    }
    reports.emplace_back(levels);
  };

  std::ifstream file_stream{file_name};
  auto line = std::string{};
  while (std::getline(file_stream, line)) {
    parse_line(line);
  }

  return reports;
}

auto main(int argc, char* argv[]) -> int {
  auto reports = ParseInputFile(argv[1]);

  std::cout << std::accumulate(
      reports.cbegin(), reports.cend(), 0,
      [](int acc, const auto& report) { return acc + report.IsSafe(); });
}
