#include <bits/stdc++.h>
#include <gtest/gtest.h>

using namespace std;

class Solution {
 public:
  int numSubarrayProductLessThanK(vector<int>& nums, int k) {
    int ans{0};
    double product{1};
    int j{0};
    for (int i{0}; i < nums.size(); i++) {
      if (i - 1 >= 0) product /= nums[i - 1];
      while (j < nums.size() && product * nums[j] < k) product *= nums[j++];
      ans += max(0, j - i);
    }

    return ans;
  }
};

TEST(SolutionTest, Test1) {
  Solution solution;
  vector<int> nums{10, 5, 2, 6};
  EXPECT_EQ(8, solution.numSubarrayProductLessThanK(nums, 100));
}

TEST(SolutionTest, Test2) {
  Solution solution;
  vector<int> nums{1, 2, 3};
  EXPECT_EQ(0, solution.numSubarrayProductLessThanK(nums, 0));
}
