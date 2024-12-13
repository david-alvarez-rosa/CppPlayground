#include <climits>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

struct Pos {
  int row;
  int col;
};

class Arcade {
 public:
  explicit Arcade(Pos button_a_delta, Pos button_b_delta,
                  Pos prize_pos) noexcept
      : button_a_delta_{button_a_delta},
        button_b_delta_{button_b_delta},
        prize_pos_{prize_pos} {}

  [[__nodiscard__]] auto MinimumTokens(Pos pos = {0, 0}) const noexcept -> int {
    /* clang-format off

       Just solve equation (vectorial):

         button_a_delta_*times_a + button_b_delta_*times_b = prize_pos_

       Expanding in axes (row, col):

         button_a_delta_.row*times_a + button_b_delta_.row*times_b = prize_pos_.row
         button_a_delta_.col*times_a + button_b_delta_.col*times_b = prize_pos_.col

       Solving by Cramer's rule https://en.wikipedia.org/wiki/Cramer%27s_rule


         x = (c1*b2 - b1*c2) / det
         y = (a1 * c2 - c1*a2) / det

       where det = a1*b2 - b1*a2

       clang-format on
    */

    auto a1 = button_a_delta_.row;
    auto a2 = button_a_delta_.col;
    auto b1 = button_b_delta_.row;
    auto b2 = button_b_delta_.col;
    auto c1 = prize_pos_.row;
    auto c2 = prize_pos_.col;

    auto det = a1 * b2 - b1 * a2;
    if (0 == det || (c1 * b2 - b1 * c2) % det != 0 ||
        (a1 * c2 - c1 * a2) % det != 0) {
      // Either determinant is 0 (no solution or infinite solutions), or the
      // solution is not an integer.  I don't handle the infinite solutions, but
      // seems is not part of my input luckily.
      return -1;
    }

    auto x = (c1 * b2 - b1 * c2) / det;
    auto y = (a1 * c2 - c1 * a2) / det;

    return 3 * x + y;
  };

 private:
  Pos button_a_delta_;
  Pos button_b_delta_;
  Pos prize_pos_;
};

auto ParseInputFile(const std::string& file_name) -> std::vector<Arcade> {
  static auto button_a_regex =
      std::regex{R"(Button A:\s*X\+(\d+),\s*Y\+(\d+))"};
  static auto button_b_regex =
      std::regex{R"(Button B:\s*X\+(\d+),\s*Y\+(\d+))"};
  static auto prize_regex = std::regex{R"(Prize:\s*X=(\d+),\s*Y=(\d+))"};
  auto arcades = std::vector<Arcade>{};
  auto file_stream = std::ifstream{file_name};
  auto line = std::string{};
  auto button_a_delta = Pos{};
  auto button_b_delta = Pos{};
  auto prize_pos = Pos{};

  while (std::getline(file_stream, line)) {
    std::smatch match;
    if (std::regex_match(line, match, button_a_regex)) {
      button_a_delta = {std::stoi(match[1]), std::stoi(match[2])};
    } else if (std::regex_match(line, match, button_b_regex)) {
      button_b_delta = {std::stoi(match[1]), std::stoi(match[2])};
    } else if (std::regex_match(line, match, prize_regex)) {
      prize_pos = {std::stoi(match[1]), std::stoi(match[2])};
    } else if (line.empty()) {
      arcades.emplace_back(button_a_delta, button_b_delta, prize_pos);
    }
  }
  arcades.emplace_back(button_a_delta, button_b_delta, prize_pos);

  return arcades;
}

auto main(int argc, char* argv[]) -> int {
  auto arcades = ParseInputFile(argv[1]);

  auto total_tokens{0};
  for (auto& arcade : arcades) {
    auto tokens = arcade.MinimumTokens();
    if (-1 != tokens) {
      total_tokens += tokens;
    }
  }

  std::cout << total_tokens << "\n";
}
