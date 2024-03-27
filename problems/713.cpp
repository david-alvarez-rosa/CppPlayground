#include <bits/stdc++.h>
#include <gtest/gtest.h>

#include <numeric>

using namespace std;

class Solution {
 public:
  int numSubarrayProductLessThanK(vector<int>& nums, int k) {
    int ans{0};
    for (size_t i{0}; i < nums.size(); i++)
      for (size_t j{i}; j < nums.size(); j++)
        if (accumulate(nums.cbegin() + i, nums.cbegin() + j + 1, 1,
                       multiplies<int>()) < k)
          ans++;

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
