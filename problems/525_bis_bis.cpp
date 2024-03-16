#include <bits/stdc++.h>
#include <gtest/gtest.h>

using namespace std;

class Solution {
 public:
  int findMaxLength(vector<int>& nums) {
    unordered_map<int, int> mp;
    for (int i{0}; i < nums.size(); i++) {
      if (nums[i])
        mp[i] = mp[i - 1] + 1;
      else
        mp[i] = mp[i - 1];
    }

    int ans{0};
    for (int i{0}; i < nums.size(); i++) {
      int j = nums.size();
      while (j >= i) {
        j--;
        if (2 * (mp[j] - mp[i - 1]) == j - i + 1) {
          ans = max(ans, j - i + 1);
          break;
        }
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

TEST(SolutionTest, Test8) {
  Solution solution;
  vector<int> nums{0, 1, 0, 1};
  EXPECT_EQ(4, solution.findMaxLength(nums));
}
