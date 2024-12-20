#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using Design = std::string;
using Pattern = std::string;

class TowelDesigner final {
 public:
  explicit TowelDesigner(const std::vector<Pattern> patterns) noexcept
      : patterns_{patterns} {}

  [[nodiscard]] auto inline IsValidDesign(const Design& design) const noexcept
      -> int64_t {
    auto dp = std::vector<int64_t>(100, -1);
    return IsValidDesignMemoize(design, 0, dp);
  }

 private:
  std::vector<Pattern> patterns_;

  [[nodiscard]] auto IsValidDesignMemoize(
      const Design& design, size_t start,
      std::vector<int64_t>& dp) const noexcept -> int64_t {
    auto& x = dp[start];

    if (-1 != x) {
      return x;
    }

    auto design_length = design.length();
    if (start == design_length) {
      return x = 1;
    }

    x = 0;
    for (const auto& pattern : patterns_) {
      auto pattern_length = pattern.length();
      if (start + pattern_length > design_length) {
        continue;
      }

      if (pattern == design.substr(start, pattern_length)) {
        x += IsValidDesignMemoize(design, start + pattern_length, dp);
      }
    }

    return x;
  }
};

auto ParseInputFile(const std::string& file_name)
    -> std::pair<TowelDesigner, std::vector<Design>> {
  auto patterns = std::vector<Pattern>{};
  auto designs = std::vector<Design>{};
  auto file_stream = std::ifstream{file_name};
  auto line = std::string{};

  // 1. Patterns
  std::getline(file_stream, line);
  auto line_stream = std::istringstream{line};
  auto pattern = Pattern{};
  while (std::getline(line_stream, pattern, ',')) {
    if (pattern[0] == ' ') {
      pattern = pattern.substr(1);
    }
    patterns.push_back(pattern);
  }

  // 2. Designs
  std::getline(file_stream, line);
  while (std::getline(file_stream, line)) {
    designs.push_back(line);
  }

  return {TowelDesigner{patterns}, designs};
}

auto main(int argc, char* argv[0]) -> int {
  auto [towel_designer, designs] = ParseInputFile(argv[1]);
  auto valid_design_count{0};
  auto count{0L};
  for (const auto& design : designs) {
    count += towel_designer.IsValidDesign(design);
  }
  std::cout << count << std::endl;
}
