#include <bits/stdc++.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace std;
using namespace testing;

class Solution {
 public:
  vector<int> sortedSquares(vector<int>& nums) {
    size_t mid{0};
    while (mid < nums.size() && nums[mid] < 0) mid++;

    vector<int> ans;
    ans.reserve(nums.size());

    int i = mid - 1, j = mid;
    while (i >= 0 || j < nums.size()) {
      if (i < 0) {
        ans.emplace_back(nums[j] * nums[j]);
        ++j;
      } else if (j == nums.size() || -nums[i] < nums[j]) {
        ans.emplace_back(nums[i] * nums[i]);
        i--;
      } else {
        ans.emplace_back(nums[j] * nums[j]);
        ++j;
      }
    }

    return ans;
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

TEST(SolutionTest, Test3) {
  Solution solution;
  vector<int> nums{-4, -1, 0, 3, 10};
  EXPECT_THAT(solution.sortedSquares(nums),
              UnorderedElementsAre(0, 1, 9, 16, 100));
}

TEST(SolutionTest, Test5) {
  Solution solution;
  vector<int> nums{-1};
  EXPECT_THAT(solution.sortedSquares(nums), UnorderedElementsAre(1));
}
