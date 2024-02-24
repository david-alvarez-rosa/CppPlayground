#include <bits/stdc++.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace std;
using namespace testing;

class Solution {
 public:
  vector<int> twoSum(vector<int>& nums, int target) {
    for (int i{0}; i < nums.size(); i++)
      for (int j{i + 1}; j < nums.size(); j++)
        if (nums[i] + nums[j] == target) return {i, j};
    return {0, 0};
  }
};

TEST(SolutionTest, Test1) {
  Solution solution;
  vector<int> nums{2, 7, 11, 15};
  EXPECT_THAT(solution.twoSum(nums, 9), UnorderedElementsAre(0, 1));
}

TEST(SolutionTest, Test2) {
  Solution solution;
  vector<int> nums{3, 2, 4};
  EXPECT_THAT(solution.twoSum(nums, 6), UnorderedElementsAre(1, 2));
}

TEST(SolutionTest, Test3) {
  Solution solution;
  vector<int> nums{3, 3};
  EXPECT_THAT(solution.twoSum(nums, 9), UnorderedElementsAre(0, 1));
}
