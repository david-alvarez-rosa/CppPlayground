#include <bits/stdc++.h>
#include <gtest/gtest.h>

using namespace std;

class Solution {
 public:
  int findMaxLength(vector<int>& nums) {
    unordered_map<int, int> mp;
    mp[0] = -1;
    int count{0}, ans{0};
    for (int i{0}; i < nums.size(); i++) {
      count = count + (nums[i] ? 1 : -1);
      if (mp.contains(count))
        ans = max(ans, i - mp[count]);
      else
        mp[count] = i;
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

TEST(SolutionTest, Test8) {
  Solution solution;
  vector<int> nums{0, 1, 0, 1};
  EXPECT_EQ(4, solution.findMaxLength(nums));
}
