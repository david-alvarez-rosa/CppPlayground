#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using Program = std::vector<int>;

class Computer final {
 public:
  explicit Computer(int register_a, int register_b, int register_c) noexcept
      : register_a_{register_a},
        register_b_{register_b},
        register_c_{register_c} {}

  auto RunProgram(const Program& program) noexcept -> std::string {
    auto out = std::string{};
    while (instruction_pointer_ + 1 < program.size()) {
      out += ExecuteInstruction(program[instruction_pointer_],
                                program[instruction_pointer_ + 1]);
    }

    return out.substr(0, out.length() - 1);
  }

  auto ExecuteInstruction(int opcode, int operand) noexcept -> std::string {
    switch (opcode) {
      case 0: {
        Adv(operand);
        return "";
      }
      case 1: {
        Bxl(operand);
        return "";
      }
      case 2: {
        Bst(operand);
        return "";
      }
      case 3: {
        Jnz(operand);
        return "";
      }
      case 4: {
        Bxc(operand);
        return "";
      }
      case 5: {
        return Out(operand);
      }
      case 6: {
        Bdv(operand);
        return "";
      }
      case 7: {
        Cdv(operand);
        return "";
      }
      default: {
        [[unlikely]] std::unreachable();
        return "";
      }
    }
  }

 private:
  int register_a_;
  int register_b_;
  int register_c_;
  int instruction_pointer_{0};

  auto inline GetComboOperand(int operand) const noexcept -> int {
    if (4 == operand) {
      return register_a_;
    }
    if (5 == operand) {
      return register_b_;
    }
    if (6 == operand) {
      return register_c_;
    }

    return operand;
  }

  auto inline Adv(int operand) noexcept -> void {
    register_a_ =
        static_cast<int>(register_a_ / std::pow(2, GetComboOperand(operand)));
    instruction_pointer_ += 2;
  }

  auto inline Bxl(int operand) noexcept -> void {
    register_b_ ^= operand;
    instruction_pointer_ += 2;
  }

  auto inline Bst(int operand) noexcept -> void {
    register_b_ = GetComboOperand(operand) % 8;
    instruction_pointer_ += 2;
  }

  auto inline Jnz(int operand) noexcept -> void {
    if (0 != register_a_) {
      instruction_pointer_ = operand;
      return;
    }
    instruction_pointer_ += 2;
  }

  auto inline Bxc([[maybe_unused]] int operand) noexcept -> void {
    register_b_ ^= register_c_;
    instruction_pointer_ += 2;
  }

  auto inline Out(int operand) noexcept -> std::string {
    instruction_pointer_ += 2;
    return std::to_string(GetComboOperand(operand) % 8) + ",";
  }

  auto inline Bdv(int operand) noexcept -> void {
    register_b_ =
        static_cast<int>(register_a_ / std::pow(2, GetComboOperand(operand)));
    instruction_pointer_ += 2;
  }

  auto inline Cdv(int operand) noexcept -> void {
    register_c_ =
        static_cast<int>(register_a_ / std::pow(2, GetComboOperand(operand)));
    instruction_pointer_ += 2;
  }
};

auto ParseInputFile(const std::string& file_name) noexcept
    -> std::pair<Computer, Program> {
  auto file_stream = std::ifstream{file_name};
  auto tmp = std::string{};
  auto register_a{0}, register_b{0}, register_c{0};
  file_stream >> tmp >> tmp >> register_a;
  file_stream >> tmp >> tmp >> register_b;
  file_stream >> tmp >> tmp >> register_c;
  file_stream >> tmp >> tmp;

  auto program = std::vector<int>{};
  auto line_stream = std::istringstream{tmp};
  auto instruction = std::string{};
  while (std::getline(line_stream, instruction, ',')) {
    program.push_back(std::stoi(instruction));
  }

  return {Computer{register_a, register_b, register_c}, program};
}

auto main(int argc, char* argv[]) -> int {
  auto [computer, program] = ParseInputFile(argv[1]);
  std::cout << computer.RunProgram(program) << "\n";
}
