#include <bits/stdc++.h>
#include <gtest/gtest.h>

using namespace std;

class Solution {
 public:
  int tribonacci(int n) {
    if (n == 0) return 0;
    if (n == 1 || n == 2) return 1;
    return tribonacci(n - 1) + tribonacci(n - 2) + tribonacci(n - 3);
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
