#include <bits/stdc++.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace std;

class Solution {
 public:
  int lengthOfLIS(vector<int>& nums, int prev = -1, int start = 0) {
    if (start == nums.size()) return 0;
    int ans = lengthOfLIS(nums, prev, start + 1);
    if (prev == -1 || nums[start] > nums[prev])
      ans = max(ans, 1 + lengthOfLIS(nums, start, start + 1));
    return ans;
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
