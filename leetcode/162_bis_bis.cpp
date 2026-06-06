#include <bits/stdc++.h>
#include <gtest/gtest.h>

using namespace std;

class Solution {
 public:
  int findPeakElement(vector<int>& nums) {
    size_t left{0}, right{nums.size() - 1};
    while (left < right) {
      auto mid = (left + right) >> 1;
      if (nums[mid] > nums[mid + 1])
        right = mid;
      else
        left = mid + 1;
    }
    return left;
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
  EXPECT_EQ(5, solution.findPeakElement(nums));
}
