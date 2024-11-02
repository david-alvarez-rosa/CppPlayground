#include <bits/stdc++.h>
#include <gtest/gtest.h>

using namespace std;

class Solution {
 public:
  int tribonacci(int n) {
    vector<int> dp(38);
    dp[0] = 0;
    dp[1] = 1;
    dp[2] = 1;
    for (int i{3}; i <= n; i++) dp[i] = dp[i - 1] + dp[i - 2] + dp[i - 3];
    return dp[n];
  }
};

TEST(SolutionTest, Test1) {
  Solution solution;
  EXPECT_EQ(4, solution.tribonacci(4));
}

TEST(SolutionTest, Test2) {
  Solution solution;
  EXPECT_EQ(1389537, solution.tribonacci(25));
}
