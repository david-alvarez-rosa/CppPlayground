#include <gtest/gtest.h>

#include <vector>

class Solution {
  std::vector<std::vector<int>> classes_;
  std::vector<std::vector<double>> dp_;
  std::size_t n_;

  [[nodiscard]]
  auto f(int extraStudents, std::size_t start) noexcept -> double {
    if (start == n_) {
      return 0.0;
    }

    auto& x = dp_[extraStudents][start];

    if (x != -1) {  // add eps
      return x;
    }

    auto ans = 0.0;

    for (auto i = 0; i <= extraStudents; ++i) {
      ans = std::max(ans, (static_cast<double>(classes_[start][0] + i) /
                           (classes_[start][1] + i)) /
                                  n_ +
                              f(extraStudents - i, start + 1));
    }

    return x = ans;
  }

 public:
  [[nodiscard]]
  auto maxAverageRatio(const std::vector<std::vector<int>>& classes,
                       int extraStudents) noexcept -> double {
    classes_ = std::move(classes);
    n_ = classes.size();
    dp_ = std::vector<std::vector<double>>(
        extraStudents + 1,
        std::vector<double>(n_, -1.0));  // (extraStudents, start) -> memoize;
    return f(extraStudents, 0);
  }
};

TEST(Solution, Test1) {
  auto classes = std::vector<std::vector<int>>{{1, 2}, {3, 5}, {2, 2}};
  EXPECT_NEAR(0.78333, Solution{}.maxAverageRatio(classes, 2), 1e-5);
}

TEST(Solution, Test2) {
  auto classes = std::vector<std::vector<int>>{{2, 4}, {3, 9}, {4, 5}, {2, 10}};
  EXPECT_NEAR(0.53485, Solution{}.maxAverageRatio(classes, 4), 1e-5);
}
