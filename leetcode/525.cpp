#include <bits/stdc++.h>
#include <gtest/gtest.h>

using namespace std;

class Solution {
 public:
  int findMaxLength(vector<int>& nums) {
    int ans{0};

    for (int i{0}; i < nums.size(); i++) {
      int num_zeros{0}, num_ones{0};
      for (int j{i}; j < nums.size(); j++) {
        if (nums[j] == 0)
          num_zeros++;
        else
          num_ones++;
        if (num_zeros == num_ones) ans = max(ans, j - i + 1);
      }
    }

    return ans;
  }
};

TEST(SolutionTest, Test1) {
  Solution solution;
  vector<int> nums{0, 1};
  EXPECT_EQ(2, solution.findMaxLength(nums));
}

TEST(SolutionTest, Test2) {
  Solution solution;
  vector<int> nums{0, 1, 0};
  EXPECT_EQ(2, solution.findMaxLength(nums));
}
