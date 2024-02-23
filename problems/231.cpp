#include <gtest/gtest.h>

#include "bits/stdc++.h"
using namespace std;

class Solution {
 public:
  bool isPowerOfTwo(int n) {
    if (n == 0) {
      return false;
    }
    if (n == 1) {
      return true;
    }
    if (n % 2 != 0) {
      return false;
    }
    return isPowerOfTwo(n / 2);
  }
};

TEST(SolutionTest, Test1) {
  Solution solution;
  EXPECT_TRUE(solution.isPowerOfTwo(1));
}

TEST(SolutionTest, Test2) {
  Solution solution;
  EXPECT_TRUE(solution.isPowerOfTwo(16));
}

TEST(SolutionTest, Test3) {
  Solution solution;
  EXPECT_FALSE(solution.isPowerOfTwo(3));
}
