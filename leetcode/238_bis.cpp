#include <bits/stdc++.h>
#include <gtest/gtest.h>

using namespace std;

class Solution {
 public:
  vector<int> productExceptSelf(vector<int>& nums) {
    int n = nums.size();

    vector<int> prefix_prod(n, 1);
    for (auto i{1}; i < n; ++i) {
      prefix_prod[i] = prefix_prod[i - 1] * nums[i - 1];
    }

    vector<int> suffix_prod(n, 1);
    for (auto i{n - 2}; i >= 0; --i) {
      suffix_prod[i] = suffix_prod[i + 1] * nums[i + 1];
    }

    vector<int> ans(n);
    ans[0] = suffix_prod[0];
    for (auto i{1}; i < n; ++i) {
      ans[i] = suffix_prod[i] * prefix_prod[i];
    }

    return ans;
  }
};

TEST(SolutionTest, Test1) {
  Solution solution;
  vector<int> nums{1, 2, 3, 4};
  vector<int> sol{24, 12, 8, 6};
  EXPECT_EQ(sol, solution.productExceptSelf(nums));
}

TEST(SolutionTest, Test2) {
  Solution solution;
  vector<int> nums{-1, 1, 0, -3, 3};
  vector<int> sol{0, 0, 9, 0, 0};
  EXPECT_EQ(sol, solution.productExceptSelf(nums));
}
