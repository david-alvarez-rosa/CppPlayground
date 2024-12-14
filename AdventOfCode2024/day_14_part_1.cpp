#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct Robot {
  int pos_x;
  int pos_y;
  int v_x;
  int v_y;
};

class BathroomSecurity final {
 public:
  explicit BathroomSecurity(std::vector<Robot> robots)
      : robots_{std::move(robots)} {}

  auto Step() noexcept -> void {
    for (auto& robot : robots_) {
      robot.pos_x += robot.v_x + width;  // Hack - force possitive (modular)
      robot.pos_x %= width;
      robot.pos_y += robot.v_y + heigth;
      robot.pos_y %= heigth;
    }
  }

  auto Iterate(int iterations) noexcept -> void {
    while (iterations--) {
      Step();
    }
  }

  [[nodiscard]] auto ComputeSafetyFactor() const noexcept -> int {
    auto robots_first_quad{0}, robots_second_quad{0}, robots_third_quad{0},
        robots_fourth_quad{0};

    for (const auto& robot : robots_) {
      if (robot.pos_x < width / 2) {
        if (robot.pos_y < heigth / 2) {
          ++robots_first_quad;
        } else if (robot.pos_y > heigth / 2) {
          ++robots_third_quad;
        }
      } else if (robot.pos_x > width / 2) {
        if (robot.pos_y < heigth / 2) {
          ++robots_second_quad;
        } else if (robot.pos_y > heigth / 2) {
          ++robots_fourth_quad;
        }
      }
    }

    return robots_first_quad * robots_second_quad * robots_third_quad *
           robots_fourth_quad;
  }

 private:
  std::vector<Robot> robots_;
  constexpr const static auto width{101};
  constexpr const static auto heigth{103};
};

auto ParseInputFile(const std::string& file_name) -> std::vector<Robot> {
  auto robots = std::vector<Robot>{};
  auto file_stream = std::ifstream{file_name};
  auto line = std::string{};

  while (std::getline(file_stream, line)) {
    auto robot = Robot{};
    auto line_stream = std::istringstream{line};
    char tmp;
    line_stream >> tmp >> tmp >> robot.pos_x >> tmp >> robot.pos_y;
    line_stream >> tmp >> tmp >> robot.v_x >> tmp >> robot.v_y;
    robots.push_back(robot);
  }

  return robots;
}

auto main(int argc, char* argv[]) -> int {
  auto robots = ParseInputFile(argv[1]);
  auto bathroom_security = BathroomSecurity{robots};
  bathroom_security.Iterate(100);
  std::cout << bathroom_security.ComputeSafetyFactor() << std::endl;
}
