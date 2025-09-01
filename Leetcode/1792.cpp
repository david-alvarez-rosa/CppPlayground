#include <gtest/gtest.h>

#include <vector>

class Solution {
 public:
  [[nodiscard]]
  static auto maxAverageRatio(const std::vector<std::vector<int>>& classes,
                              int extraStudents, std::size_t start = 0) noexcept
      -> double {
    if (start == classes.size()) {
      return 0.0;
    }

    auto ans = 0.0;

    for (auto i = 0; i <= extraStudents; ++i) {
      ans = std::max(
          ans, (static_cast<double>(classes[start][0] + i) /
                (classes[start][1] + i)) /
                       static_cast<double>(classes.size()) +
                   maxAverageRatio(classes, extraStudents - i, start + 1));
    }

    return ans;
  }
};

TEST(Solution, Test1) {
  auto classes = std::vector<std::vector<int>>{{1, 2}, {3, 5}, {2, 2}};
  EXPECT_NEAR(0.78333, Solution::maxAverageRatio(classes, 2), 1e-5);
}

TEST(Solution, Test2) {
  auto classes = std::vector<std::vector<int>>{{2, 4}, {3, 9}, {4, 5}, {2, 10}};
  EXPECT_NEAR(0.53485, Solution::maxAverageRatio(classes, 4), 1e-5);
}
