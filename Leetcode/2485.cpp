#include <bits/stdc++.h>
#include <gtest/gtest.h>

using namespace std;

class Solution {
 public:
  /* Explanation:
     sum from 1 to x = x*(x + 1)/2
     sum from x to n = (n + x)*(n - x - 1)/2
     x*(x + 1)/2 = (n + x)*(n - x + 1)/2
     x*(x + 1) = (n + x)*(n - x + 1)
     x^2 + x = n^2 -n*x + n + n*x - x^2 + x
     2*x^2 = n + n^2
     x = sqrt(n*(n + 1)/2)
  */
  int pivotInteger(int n) {
    double ans = sqrt(n * (n + 1) / 2);
    return ans - (int)ans > kEps ? -1 : ans;
  }

 private:
  const double kEps{1e-6};
};

TEST(SolutionTest, Test1) {
  Solution solution;
  EXPECT_EQ(6, solution.pivotInteger(8));
}

TEST(SolutionTest, Test2) {
  Solution solution;
  EXPECT_EQ(1, solution.pivotInteger(1));
}

TEST(SolutionTest, Test3) {
  Solution solution;
  EXPECT_EQ(-1, solution.pivotInteger(4));
}
