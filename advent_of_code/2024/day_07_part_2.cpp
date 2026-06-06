#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class CalibrationEquation final {
 public:
  explicit CalibrationEquation(uint64_t total,
                               std::vector<int> operands) noexcept
      : total_{total}, operands_{std::move(operands)} {}

  auto IsSolvable(size_t start = 0, int64_t curr_total = 0) const noexcept
      -> bool {
    if (start == operands_.size()) [[__unlikely__]] {
      return curr_total == total_;
    }

    if (curr_total > total_) {
      return false;
    }

    if (IsSolvable(start + 1, curr_total + operands_[start]) ||
        IsSolvable(start + 1, curr_total * operands_[start]) ||
        IsSolvable(start + 1, ConcatOperator(curr_total, operands_[start]))) {
      return true;
    }

    return false;
  }

  __attribute__((always_inline)) inline auto GetTotal() const noexcept
      -> uint64_t {
    return total_;
  }

 private:
  uint64_t total_;
  std::vector<int> operands_;

  __attribute__((always_inline)) inline static auto ConcatOperator(
      uint64_t lfs, uint64_t rhs) noexcept -> uint64_t {
    return std::stoll(std::to_string(lfs) + std::to_string(rhs));
  }
};

auto ParseInputFile(const std::string& file_name)
    -> std::vector<CalibrationEquation> {
  auto calibration_equations = std::vector<CalibrationEquation>{};
  auto file_stream = std::ifstream{file_name};
  auto line = std::string{};

  while (std::getline(file_stream, line)) {
    auto total = std::string{};
    auto line_stream = std::istringstream{line};
    std::getline(line_stream, total, ':');

    auto operands_raw = std::string{};
    auto operands = std::vector<int>{};
    std::getline(line_stream, operands_raw);
    std::istringstream operands_stream(operands_raw);
    auto operand{0};
    while (operands_stream >> operand) {
      operands.emplace_back(operand);
    }

    calibration_equations.emplace_back(std::stoll(total), operands);
  }

  return calibration_equations;
}

auto main(int argc, char* argv[]) -> int {
  auto calibration_equations = ParseInputFile(argv[1]);

  uint64_t total_calibration_result = 0;
  for (const auto& calibration_equation : calibration_equations) {
    if (calibration_equation.IsSolvable()) {
      total_calibration_result += calibration_equation.GetTotal();
    }
  }

  std::cout << total_calibration_result << std::endl;
}
