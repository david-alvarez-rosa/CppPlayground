#include <gtest/gtest.h>

#include <cstddef>
#include <vector>

class Solution {
 public:
  int subarraySum(std::vector<int>& nums, int k, int start = 0) {
    auto ans = 0;
    for (std::size_t i = 0; i < nums.size(); ++i) {
      auto sum = 0;
      for (std::size_t j = i; j < nums.size(); ++j) {
        sum += nums[j];
        if (sum == k) {
          ++ans;
        }
      }
    }
    return ans;
  }
};

TEST(SolutionTest, Test1) {
  Solution solution;
  std::vector<int> nums{1, 1, 1};
  EXPECT_EQ(2, solution.subarraySum(nums, 2));
}

TEST(SolutionTest, Test2) {
  Solution solution;
  std::vector<int> nums{1, 2, 3};
  EXPECT_EQ(2, solution.subarraySum(nums, 3));
}
