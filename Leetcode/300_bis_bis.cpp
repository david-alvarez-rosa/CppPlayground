#include <bits/stdc++.h>
#include <gtest/gtest.h>

using namespace std;

class Solution {
 public:
  int lengthOfLIS(vector<int>& nums) {
    dp_ =
        vector<vector<int>>(nums.size() + 1, vector<int>(nums.size() + 1, -1));
    nums_ = std::move(nums);
    return f(0, nums_.size());
  }

 private:
  int f(int start, int prev) {
    auto& x = dp_[start][prev];
    if (x != -1) return x;
    if (start == nums_.size()) return x = 0;
    int ans = f(start + 1, prev);
    if (prev == nums_.size() || nums_[start] > nums_[prev])
      ans = max(ans, 1 + f(start + 1, start));
    return x = ans;
  }

  vector<vector<int>> dp_;
  vector<int> nums_;
};

TEST(SolutionTest, Test1) {
  Solution solution;
  vector<int> nums{10, 9, 2, 5, 3, 7, 101, 18};
  EXPECT_EQ(4, solution.lengthOfLIS(nums));
}

TEST(SolutionTest, Test2) {
  Solution solution;
  vector<int> nums{0, 1, 0, 3, 2, 3};
  EXPECT_EQ(4, solution.lengthOfLIS(nums));
}

TEST(SolutionTest, Test3) {
  Solution solution;
  vector<int> nums{7, 7, 7, 7, 7, 7, 7};
  EXPECT_EQ(1, solution.lengthOfLIS(nums));
}
