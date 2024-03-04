#include <bits/stdc++.h>
#include <gtest/gtest.h>

using namespace std;

class Solution {
 public:
  bool increasingTriplet(vector<int>& nums) {
    for (size_t i{0}; i < nums.size(); i++)
      for (size_t j{i + 1}; j < nums.size(); j++)
        for (size_t k{j + 1}; k < nums.size(); k++)
          if (nums[i] < nums[j] && nums[j] < nums[k]) return true;
    return false;
  }
};

TEST(SolutionTest, Test1) {
  Solution solution;
  vector<int> nums{1, 2, 3, 4, 5};
  EXPECT_TRUE(solution.increasingTriplet(nums));
}

TEST(SolutionTest, Test2) {
  Solution solution;
  vector<int> nums{5, 4, 3, 2, 1};
  EXPECT_FALSE(solution.increasingTriplet(nums));
}

TEST(SolutionTest, Test3) {
  Solution solution;
  vector<int> nums{2, 1, 5, 0, 4, 6};
  EXPECT_TRUE(solution.increasingTriplet(nums));
}
