#include <bits/stdc++.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace std;
using namespace testing;

class Solution {
 public:
  vector<int> productExceptSelf(vector<int>& nums) {
    const auto n{nums.size()};
    vector<int> ans(n);
    ans[0] = nums[0];
    for (size_t i{1}; i < n; i++) ans[i] = nums[i] * ans[i - 1];
    long acc{1};
    for (size_t i{n - 1}; i >= 1; i--) {
      ans[i] = ans[i - 1] * acc;
      acc *= nums[i];
    }
    ans[0] = acc;
    return ans;
  }
};

TEST(SolutionTest, Test1) {
  Solution solution;
  vector<int> nums{1, 2, 3, 4};
  EXPECT_THAT(solution.productExceptSelf(nums), ElementsAre(24, 12, 8, 6));
}

TEST(SolutionTest, Test2) {
  Solution solution;
  vector<int> nums{-1, 1, 0, -3, 3};
  EXPECT_THAT(solution.productExceptSelf(nums), ElementsAre(0, 0, 9, 0, 0));
}
