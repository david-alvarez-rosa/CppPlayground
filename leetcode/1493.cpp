#include <gtest/gtest.h>

#include <vector>

class Solution {
 public:
  static int longestSubarray(std::vector<int>& nums) {
    auto ans = 0, ones = 0;

    for (std::size_t left = 0, right = 0, n = nums.size(); right < n; right++) {
      if (1 == nums[right]) ++ones;
      while (right - left > ones) {
        if (1 == nums[left]) --ones;
        ++left;
      }
      ans = std::max(ans, ones);
    }

    return ans == nums.size() ? ans - 1 : ans;
  }
};

TEST(SolutionTest, Test1) {
  std::vector<int> nums{1, 1, 0, 1};
  EXPECT_EQ(3, Solution::longestSubarray(nums));
}

TEST(SolutionTest, Test2) {
  std::vector<int> nums{0, 1, 1, 1, 0, 1, 1, 0, 1};
  EXPECT_EQ(5, Solution::longestSubarray(nums));
}

TEST(SolutionTest, Test3) {
  std::vector<int> nums{1, 1, 1};
  EXPECT_EQ(2, Solution::longestSubarray(nums));
}
