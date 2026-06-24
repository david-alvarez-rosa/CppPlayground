#include <gtest/gtest.h>

#include <climits>
#include <string>
#include <unordered_map>

class Solution {
public:
  auto maxNumberOfBalloons(std::string text) noexcept -> int {
    auto target = std::string{"balloon"};
    auto fqs = std::unordered_map<char, int>{};
    for (auto c : text) {
      if (std::string("ban").contains(c)) fqs[c] += 2;
      else if (std::string("ol").contains(c)) ++fqs[c];
    }

    auto ans = INT_MAX;

    if (fqs.size() < 5) return 0;

    for (auto [_, fq] : fqs) {
      ans = std::min(ans, fq);
    }

    return ans / 2;
  }
};

TEST(SolutionTest, Test1) {
  auto solution = Solution{};
  EXPECT_EQ(1, solution.maxNumberOfBalloons("nlaebolko"));
}

TEST(SolutionTest, Test2) {
  auto solution = Solution{};
  EXPECT_EQ(2, solution.maxNumberOfBalloons("loonbalxballpoon"));
}

TEST(SolutionTest, Test3) {
  auto solution = Solution{};
  EXPECT_EQ(0, solution.maxNumberOfBalloons("leetcode"));
}
