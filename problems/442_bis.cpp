#include <bits/stdc++.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace std;
using namespace testing;

class Solution {
 public:
  vector<int> findDuplicates(vector<int>& nums) {
    vector<int> dups;
    dups.reserve(nums.size());
    for (const auto num : nums) {
      if (nums[abs(num) - 1] < 0) dups.emplace_back(abs(num));
      nums[abs(num) - 1] *= -1;
    }
    return dups;
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
