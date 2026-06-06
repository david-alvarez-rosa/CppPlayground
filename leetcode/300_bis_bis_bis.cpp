#include <bits/stdc++.h>
#include <gtest/gtest.h>

using namespace std;

class Solution {
 public:
  int lengthOfLIS(vector<int>& nums) {
    vector<int> dp(nums.size(), 1);
    for (size_t i{0}; i < nums.size(); i++)
      for (size_t j{0}; j < i; j++)
        if (nums[i] > nums[j]) dp[i] = max(dp[i], 1 + dp[j]);

    return *max_element(dp.cbegin(), dp.cend());
  }
};

TEST(SolutionTest, Test1) {
  Solution solution;
  vector<int> nums{10, 9, 2, 5, 3, 7, 101, 18};
  EXPECT_EQ(4, solution.lengthOfLIS(nums));
}

TEST(SolutionTest, Test2) {
  Solution solution;
  vector<int> nums{0, 1, 0, 3, 2, 3};
  EXPECT_EQ(4, solution.lengthOfLIS(nums));
}

TEST(SolutionTest, Test3) {
  Solution solution;
  vector<int> nums{7, 7, 7, 7, 7, 7, 7};
  EXPECT_EQ(1, solution.lengthOfLIS(nums));
}
