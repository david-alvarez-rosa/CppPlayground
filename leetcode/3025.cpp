#include <gtest/gtest.h>

#include <vector>

class Solution {
 public:
  [[nodiscard]]
  static auto numberOfPairs(std::vector<std::vector<int>>& points) noexcept
      -> int {
    auto ans = 0ZU, n = points.size();

    auto is_upper_left = [](auto point_a, auto point_b) {
      return point_a[0] <= point_b[0] && point_a[1] >= point_b[1];
    };
    auto no_points_inside = [&](auto point_a, auto point_b) {
      for (auto t = 0; t < n; ++t) {
        const auto& point_c = points[t];
        if (point_a == point_c or point_b == point_c) continue;

        if ((point_a[0] <= point_c[0] && point_c[0] <= point_b[0]) &&
            (point_a[1] >= point_c[1] && point_c[1] >= point_b[1])) {
          return true;
        }
      }
      return false;
    };

    for (auto i = 0ZU; i < n; ++i) {
      for (auto j = 0ZU; j < n; ++j) {
        if (i == j) continue;

        const auto& point_a = points[i];
        const auto& point_b = points[j];

        if (is_upper_left(point_a, point_b) &&
            !no_points_inside(point_a, point_b)) {
          ++ans;
        }
      }
    }

    return ans;
  }
};

TEST(SolutionTest, Test1) {
  auto points = std::vector<std::vector<int>>{{1, 1}, {2, 2}, {3, 3}};
  EXPECT_EQ(Solution::numberOfPairs(points), 0);
}

TEST(SolutionTest, Test2) {
  auto points = std::vector<std::vector<int>>{{6, 2}, {4, 4}, {2, 6}};
  EXPECT_EQ(Solution::numberOfPairs(points), 2);
}

TEST(SolutionTest, Test3) {
  auto points = std::vector<std::vector<int>>{{3, 1}, {1, 3}, {1, 1}};
  EXPECT_EQ(Solution::numberOfPairs(points), 2);
}
