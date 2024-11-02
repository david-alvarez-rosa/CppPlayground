#include <bits/stdc++.h>
#include <gtest/gtest.h>

using namespace std;

class Solution {
 public:
  long long countSubarrays(vector<int>& nums, int k) {
    int maxi = *max_element(nums.cbegin(), nums.cend()), count{0};
    long long ans{0};
    for (int i{0}, j{0}; j < nums.size(); j++) {
      count += nums[j] == maxi;
      while (count >= k) count -= nums[i++] == maxi;
      ans += i;
    }
    return ans;
  }
};

TEST(SolutionTest, Test1) {
  Solution solution;
  vector<int> nums{1, 3, 2, 3, 3};
  EXPECT_EQ(6, solution.countSubarrays(nums, 2));
}

TEST(SolutionTest, Test2) {
  Solution solution;
  vector<int> nums{1, 4, 2, 1};
  EXPECT_EQ(0, solution.countSubarrays(nums, 3));
}
