#include <bits/stdc++.h>
#include <gtest/gtest.h>

using namespace std;

class Solution {
 public:
  int maxSubarrayLength(vector<int>& nums, int k) {
    int ans{0};
    unordered_map<int, int> fqs;
    for (int i{0}, j{0}; j < nums.size(); j++) {
      fqs[nums[j]]++;
      while (i <= j && fqs[nums[j]] > k) fqs[nums[i++]]--;
      ans = max(ans, j - i + 1);
    }
    return ans;
  }
};

TEST(SolutionTest, Test1) {
  Solution solution;
  vector<int> nums{1, 2, 3, 1, 2, 3, 1, 2};
  EXPECT_EQ(6, solution.maxSubarrayLength(nums, 2));
}

TEST(SolutionTest, Test2) {
  Solution solution;
  vector<int> nums{1, 2, 1, 2, 1, 2, 1, 2};
  EXPECT_EQ(2, solution.maxSubarrayLength(nums, 1));
}

TEST(SolutionTest, Test3) {
  Solution solution;
  vector<int> nums{5, 5, 5, 5, 5, 5, 5};
  EXPECT_EQ(4, solution.maxSubarrayLength(nums, 4));
}
