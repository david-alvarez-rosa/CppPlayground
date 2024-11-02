#include <bits/stdc++.h>
#include <gtest/gtest.h>

using namespace std;

class Solution {
 public:
  int findPeakElement(vector<int>& nums) {
    for (size_t i{0}; i < nums.size(); i++)
      if ((i == 0 || nums[i] > nums[i - 1]) &&
          (i == nums.size() - 1 || nums[i] > nums[i + 1]))
        return i;
    return -1;
  }
};

TEST(SolutionTest, Test1) {
  Solution solution;
  vector<int> nums{1, 2, 3, 1};
  EXPECT_EQ(2, solution.findPeakElement(nums));
}

TEST(SolutionTest, Test2) {
  Solution solution;
  vector<int> nums{1, 2, 1, 3, 5, 6, 4};
  EXPECT_EQ(1, solution.findPeakElement(nums));
}
