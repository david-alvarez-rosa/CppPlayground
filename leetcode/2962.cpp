#include <bits/stdc++.h>
#include <gtest/gtest.h>

using namespace std;

class Solution {
 public:
  long long countSubarrays(vector<int>& nums, int k) {
    auto maxi = *max_element(nums.cbegin(), nums.cend());
    long long ans{0};
    for (size_t i{0}; i < nums.size(); i++)
      for (size_t j{i}; j < nums.size(); j++) {
        int count{0};
        for (size_t aux{i}; aux <= j; aux++) {
          if (nums[aux] == maxi) count++;
          if (count == k) {
            ans++;
            break;
          }
        }
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
