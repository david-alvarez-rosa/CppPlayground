#include <bits/stdc++.h>
#include <gtest/gtest.h>

using namespace std;

class Solution {
 public:
  bool rotateString(string s, string goal) {
    if (s.length() != goal.length()) return false;

    for (size_t start{0}; start < s.length(); ++start)
      if (same(start, s, goal)) return true;

    return false;
  }

 private:
  bool same(size_t start, const string& s, const string& goal) {
    auto n{s.length()};

    for (size_t i{0}; i < n; i++) {
      if (start == n) start = 0;
      if (goal[i] != s[start]) return false;
      start++;
    }

    return true;
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
