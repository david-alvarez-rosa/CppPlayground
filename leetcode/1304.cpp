#include <gtest/gtest.h>

#include <numeric>
#include <vector>

class Solution {
 public:
  [[nodiscard]]
  static auto sumZero(int num) noexcept -> std::vector<int> {
    auto ans = std::vector<int>{};
    ans.reserve(num);
    if (num % 2 == 1) {
      ans.push_back(0);
      --num;
    }
    for (; num >= 2; num -= 2) {
      ans.push_back(num);
      ans.push_back(-num);
    }
    return ans;
  }
};

TEST(Solution, Test1) {
  auto num = 5;
  auto ans = Solution::sumZero(num);
  EXPECT_EQ(ans.size(), num);
  EXPECT_EQ(std::accumulate(ans.cbegin(), ans.cend(), 0), 0);
}

TEST(Solution, Test2) {
  auto num = 3;
  auto ans = Solution::sumZero(num);
  EXPECT_EQ(ans.size(), num);
  EXPECT_EQ(std::accumulate(ans.cbegin(), ans.cend(), 0), 0);
}

TEST(Solution, Test3) {
  auto num = 1;
  auto ans = Solution::sumZero(num);
  EXPECT_EQ(ans.size(), num);
  EXPECT_EQ(std::accumulate(ans.cbegin(), ans.cend(), 0), 0);
}
