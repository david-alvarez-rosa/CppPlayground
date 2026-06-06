#include <bits/stdc++.h>
#include <gtest/gtest.h>

using namespace std;

class Solution {
 public:
  string makeGood(string s) {
    if (s.empty()) return "";
    for (size_t i{0}; i < s.size() - 1; i++)
      if (abs(s[i] - s[i + 1]) == 32) return makeGood(s.erase(i, 2));
    return s;
  }
};

TEST(SolutionTest, Test1) {
  Solution solution;
  EXPECT_EQ("leetcode", solution.makeGood("leEeetcode"));
}

TEST(SolutionTest, Test2) {
  Solution solution;
  EXPECT_EQ("", solution.makeGood("abBAcC"));
}

TEST(SolutionTest, Test3) {
  Solution solution;
  EXPECT_EQ("s", solution.makeGood("s"));
}
