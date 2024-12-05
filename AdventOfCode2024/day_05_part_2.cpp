#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using Rules = std::unordered_map<int, std::vector<int>>;
using Update = std::vector<int>;
using Updates = std::vector<Update>;

auto IsValidUpdate(const Rules& rules, const Update& update) -> bool {
  for (auto i{0U}; i < update.size(); ++i) {
    int curr_page = update[i];
    if (!rules.contains(curr_page)) {
      continue;
    }
    const auto& curr_rules = rules.at(curr_page);
    for (auto j{0U}; j < i; ++j) {
      const auto other_page = update[j];
      if (std::find(curr_rules.cbegin(), curr_rules.cend(), other_page) !=
          curr_rules.end()) {
        return false;
      }
    }
  }
  return true;
}

auto Solve(const Rules& rules, Updates& updates) -> int {
  auto ans{0};

  for (auto& update : updates) {
    if (!IsValidUpdate(rules, update)) {
      std::sort(update.begin(), update.end(),
                [&rules](const auto page_a, const auto page_b) -> bool {
                  if (rules.contains(page_b)) {
                    const auto& rules_b = rules.at(page_b);
                    if (std::find(rules_b.cbegin(), rules_b.cend(), page_a) !=
                        rules_b.end()) {
                      return false;
                    }
                  }

                  return true;
                });
      ans += update[update.size() / 2];
    }
  }

  return ans;
}

auto ParseInputFile(const std::string& file_name) -> std::pair<Rules, Updates> {
  auto rules = Rules{};
  auto updates = Updates{};
  auto split_by_comma = [](const std::string& line) -> Update {
    auto update = Update{};
    auto line_stream = std::stringstream{line};
    auto page = std::string{};

    while (getline(line_stream, page, ',')) {
      update.push_back(stoi(page));
    }

    return update;
  };
  auto is_first_part{true};
  auto file_stream = std::ifstream{file_name};
  auto line = std::string{};

  while (getline(file_stream, line)) {
    if (line.empty()) {
      is_first_part = false;
      continue;
    }

    if (is_first_part) {
      int first_page = stoi(line.substr(0, 2));
      int second_page = stoi(line.substr(3, 2));
      rules[first_page].push_back(second_page);
    } else {
      updates.emplace_back(split_by_comma(line));
    }
  }

  return {rules, updates};
}

auto main(int argc, char* argv[]) -> int {
  auto [rules, updates] = ParseInputFile(argv[1]);
  std::cout << Solve(rules, updates) << "\n";
}
