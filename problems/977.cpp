#include <bits/stdc++.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace std;
using namespace testing;

class Solution {
 public:
  vector<int> sortedSquares(vector<int>& nums) {

    for (auto& num : nums) num *= num;
    sort(nums.begin(), nums.end());
    return nums;

  }
};

TEST(SolutionTest, Test1) {
  Solution solution;
  vector<int> nums{-4, -1, 0, 3, 10};
  EXPECT_THAT(solution.sortedSquares(nums),
              UnorderedElementsAre(0, 1, 9, 16, 100));
}

TEST(SolutionTest, Test2) {
  Solution solution;
  vector<int> nums{-7, -3, 2, 3, 11};
  EXPECT_THAT(solution.sortedSquares(nums),
              UnorderedElementsAre(4, 9, 9, 49, 121));
}
