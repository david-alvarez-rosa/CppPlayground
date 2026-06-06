#include <gtest/gtest.h>

#include <unordered_map>

class Solution {
  constexpr static int kMod = 1e9 + 7;

 public:
  [[nodiscard]]
  static auto peopleAwareOfSecret(int n, int delay, int forget,
                                  int curr = 1) noexcept -> int {
    auto discovery_amount = std::unordered_map<int, int>{};
    discovery_amount[1] = 1;

    for (auto day = 2; day <= n; ++day) {
      auto num_discoveries = 0;

      for (auto& [day_discovered, amount] : discovery_amount) {
        if ((day - day_discovered) % forget == 0) {
          amount = 0;
        } else if ((day - day_discovered) >= delay) {
          num_discoveries += amount % kMod;
          num_discoveries %= kMod;
        }
      }

      discovery_amount[day] = num_discoveries;
    }

    auto ans = 0;
    for (auto [_, amount] : discovery_amount) {
      ans += amount % kMod;
      ans %= kMod;
    }

    return ans;
  }
};

TEST(Solution, Test1) { EXPECT_EQ(Solution::peopleAwareOfSecret(6, 2, 4), 5); }
TEST(Solution, Test2) { EXPECT_EQ(Solution::peopleAwareOfSecret(4, 1, 3), 6); }
TEST(Solution, Test3) {
  EXPECT_EQ(Solution::peopleAwareOfSecret(684, 18, 496), 653668527);
}
