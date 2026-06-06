#include <bits/stdc++.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace std;
using namespace testing;

class Solution {
 public:
  vector<int> findDuplicates(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    vector<int> ans;
    for (size_t i{1}; i < nums.size(); i++)
      if (nums[i] == nums[i - 1]) ans.emplace_back(nums[i]);
    return ans;
  }
};

TEST(SolutionTest, Test1) {
  Solution solution;
  vector<int> nums{4, 3, 2, 7, 8, 2, 3, 1};
  EXPECT_THAT(solution.findDuplicates(nums), UnorderedElementsAre(2, 3));
}

TEST(SolutionTest, Test2) {
  Solution solution;
  vector<int> nums{1, 1, 2};
  EXPECT_THAT(solution.findDuplicates(nums), UnorderedElementsAre(1));
}

TEST(SolutionTest, Test3) {
  Solution solution;
  vector<int> nums{1};
  EXPECT_THAT(solution.findDuplicates(nums), UnorderedElementsAre());
}
