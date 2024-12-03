#include <fstream>
#include <iostream>
#include <regex>
#include <string>

auto AddUpMultiplications(const std::vector<std::string>& corrupted_memory)
    -> int {
  auto total{0};

  for (const auto& multiplication : corrupted_memory) {
    const static auto pattern = std::regex{R"(mul\((\d{1,3}),(\d{1,3})\))"};
    auto match = std::smatch{};

    if (std::regex_match(multiplication, match, pattern)) {
      total += std::stoi(match[1].str()) * std::stoi(match[2].str());
    }
  }

  return total;
}

auto ParseInputFile(const std::string& file_name) noexcept
    -> std::vector<std::string> {
  static const auto pattern = std::regex{R"(mul\((\d{1,3}),(\d{1,3})\))"};
  auto file_stream = std::ifstream{file_name};
  auto results = std::vector<std::string>{};

  auto chunk = std::string{};
  while (file_stream >> chunk) {
    auto begin = std::sregex_iterator(chunk.begin(), chunk.end(), pattern);
    auto end = std::sregex_iterator();

    for (std::sregex_iterator i = begin; i != end; ++i) {
      auto match = *i;
      results.push_back(match.str(0));
    }
  }

  return results;
}

auto main(int argc, char* argv[]) -> int {
  auto corrupted_memory = ParseInputFile(argv[1]);
  std::cout << AddUpMultiplications(corrupted_memory) << "\n";
}
