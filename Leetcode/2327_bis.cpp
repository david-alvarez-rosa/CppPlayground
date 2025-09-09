#include <gtest/gtest.h>

#include <vector>

class Solution {
  constexpr static int kMod = 1e9 + 7;

 public:
  [[nodiscard]]
  static auto peopleAwareOfSecret(int n, int delay, int forget) noexcept
      -> int {
    auto dp = std::vector<long long>(n + 1, 0);
    dp[1] = 1;

    auto share = 0LL;
    for (auto day = 2; day <= n; ++day) {
      if (day - delay > 0) share += dp[day - delay] % kMod;
      if (day - forget > 0) share -= dp[day - forget] % kMod;
      dp[day] = share % kMod;
    }

    auto ans = 0;
    for (auto i = n - forget + 1; i <= n; ++i) {
      ans += dp[i] % kMod;
      ans %= kMod;
    }

    return ans % kMod;
  }
};

TEST(Solution, Test1) { EXPECT_EQ(Solution::peopleAwareOfSecret(6, 2, 4), 5); }
TEST(Solution, Test2) { EXPECT_EQ(Solution::peopleAwareOfSecret(4, 1, 3), 6); }
TEST(Solution, Test3) {
  EXPECT_EQ(Solution::peopleAwareOfSecret(684, 18, 496), 653668527);
}
