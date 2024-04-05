#include <bits/stdc++.h>
#include <gtest/gtest.h>

using namespace std;

class Solution {
 public:
  string makeGood(string s) {
    stack<char> ms;
    for (const auto c : s) {
      if (!ms.empty() && abs(c - ms.top()) == 32)
        ms.pop();
      else
        ms.push(c);
    }

    string ans;
    while (!ms.empty()) {
      ans = ms.top() + ans;
      ms.pop();
    }

    return ans;
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
