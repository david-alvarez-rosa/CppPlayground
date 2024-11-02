#include <bits/stdc++.h>
#include <gtest/gtest.h>

using namespace std;

class Solution {
 public:
  int findDuplicate(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    for (size_t i{1}; i < nums.size(); i++)
      if (nums[i] == nums[i - 1]) return nums[i];
    return -1;
  }
};

TEST(SolutionTest, Test1) {
  Solution solution;
  vector<int> nums{1, 3, 4, 2, 2};
  EXPECT_EQ(2, solution.findDuplicate(nums));
}

TEST(SolutionTest, Test2) {
  Solution solution;
  vector<int> nums{3, 1, 3, 4, 2};
  EXPECT_EQ(3, solution.findDuplicate(nums));
}

TEST(SolutionTest, Test3) {
  Solution solution;
  vector<int> nums{3, 3, 3, 3, 3};
  EXPECT_EQ(3, solution.findDuplicate(nums));
}
