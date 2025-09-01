#include <gtest/gtest.h>

#include <numeric>
#include <queue>
#include <vector>

class Solution {
 public:
  [[nodiscard]]
  static auto maxAverageRatio(std::vector<std::vector<int>>& classes,
                              int extraStudents) noexcept -> double {
    auto compute_delta = [](auto pass, auto total) {
      return static_cast<double>(pass + 1) / (total + 1) -
             static_cast<double>(pass) / total;
    };

    auto pq =
        std::priority_queue<std::pair<double, std::size_t>>{};  // (delta, id)

    for (auto id = 0ZU, n = classes.size(); id < n; ++id) {
      pq.emplace(compute_delta(classes[id][0], classes[id][1]), id);
    }

    while (extraStudents--) {
      auto id = pq.top().second;
      pq.pop();
      ++classes[id][0];
      ++classes[id][1];
      pq.emplace(compute_delta(classes[id][0], classes[id][1]), id);
    }

    return std::accumulate(classes.cbegin(), classes.cend(), 0.0,
                           [](auto acc, const auto& single_class) {
                             return acc + static_cast<double>(single_class[0]) /
                                              single_class[1];
                           }) /
           static_cast<double>(classes.size());
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
