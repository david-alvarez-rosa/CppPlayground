#include "bits/stdc++.h"
#include <gtest/gtest.h>
using namespace std;

class Solution {
public:
  int rangeBitwiseAnd(int left, int right) {
    int count{0};
    while (left != right) {
      left >>= 1;
      right >>= 1;
      count++;
    }
    return left << count;
  }
};

TEST(SolutionTest, Test1) {
  Solution solution;
  EXPECT_EQ(solution.rangeBitwiseAnd(4, 7), 4);
}

TEST(SolutionTest, Test2) {
  Solution solution;
  EXPECT_EQ(solution.rangeBitwiseAnd(0, 0), 0);
}

TEST(SolutionTest, Test3) {
  Solution solution;
  EXPECT_EQ(solution.rangeBitwiseAnd(1, 2147483647), 0);
}
