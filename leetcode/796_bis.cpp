#include <bits/stdc++.h>
#include <gtest/gtest.h>

using namespace std;

class Solution {
 public:
  bool rotateString(string s, string goal) {
    if (s.length() != goal.length()) return false;

    return (s + s).find(goal) != string::npos;
  }
};

TEST(SolutionTest, Test1) {
  Solution solution;
  EXPECT_TRUE(solution.rotateString("abcde", "cdeab"));
}

TEST(SolutionTest, Test2) {
  Solution solution;
  EXPECT_FALSE(solution.rotateString("abcde", "abced"));
}
