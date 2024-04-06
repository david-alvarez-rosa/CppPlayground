#include <bits/stdc++.h>
#include <gtest/gtest.h>

using namespace std;

class Solution {
 public:
  string minRemoveToMakeValid(string s) {
    for (int i{0}, open{0}, close{0}; i < s.size(); i++) {
      if (s[i] == '(') open++;
      if (s[i] == ')') close++;
      if (close > open) {
        close--;
        s[i] = '*';
      }
    }

    for (int i{0}, count_open{0}, count_close{0}; i < s.size(); i++) {
      if (s[s.size() - 1 - i] == '(') count_open++;
      if (s[s.size() - 1 - i] == ')') count_close++;
      if (count_close < count_open) {
        count_open--;
        s[s.size() - 1 - i] = '*';
      }
    }

    string ans;
    for (const auto c : s)
      if (c != '*') ans += c;

    return ans;
  }
};

TEST(SolutionTest, Test1) {
  Solution solution;
  EXPECT_EQ("lee(t(c)o)de", solution.minRemoveToMakeValid("lee(t(c)o)de)"));
}

TEST(SolutionTest, Test2) {
  Solution solution;
  EXPECT_EQ("ab(c)d", solution.minRemoveToMakeValid("a)b(c)d"));
}

TEST(SolutionTest, Test3) {
  Solution solution;
  EXPECT_EQ("", solution.minRemoveToMakeValid("))(("));
}
