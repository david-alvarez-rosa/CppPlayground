#include <gtest/gtest.h>

#include <cstdint>
#include <vector>

namespace {
[[nodiscard]] __attribute__((always_inline)) constexpr int64_t sumN(std::size_t n) {
  return n * (n + 1) / 2;
}
}  // namespace

class Solution {
 public:
  [[nodiscard]] static int64_t zeroFilledSubarray(const std::vector<int>& nums) {
    auto ans = 0LL;

    for (auto left = 0UZ, right = 0UZ, length = nums.size(); left < length; ++left) {
      if (0 == nums[left]) {
        for (right = left; right < length && 0 == nums[right]; ++right) {}
        ans += sumN(right - left);
        left = right - 1;
      }
    }

    return ans;
  }
};

TEST(SolutionTest, Test1) {
  Solution solution;
  std::vector<int> nums{1, 3, 0, 0, 2, 0, 0, 4};
  EXPECT_EQ(solution.zeroFilledSubarray(nums), 6);
}

TEST(SolutionTest, Test2) {
  Solution solution;
  std::vector<int> nums{0, 0, 0, 2, 0, 0};
  EXPECT_EQ(solution.zeroFilledSubarray(nums), 9);
}

TEST(SolutionTest, Test3) {
  Solution solution;
  std::vector<int> nums{2, 10, 2019};
  EXPECT_EQ(solution.zeroFilledSubarray(nums), 0);
}
