#include <bits/stdc++.h>
#include <gtest/gtest.h>

using namespace std;

class Solution {
 public:
  int numSubarrayProductLessThanK(vector<int>& nums, int k) {
    if (k == 0) return 0;

    int ans{0};
    double product{1};
    for (int i{0}, j{0}; j < nums.size(); j++) {
      product *= nums[j];
      while (i <= j && product >= k) product /= nums[i++];
      ans += j - i + 1;
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
