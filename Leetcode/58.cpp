#include <bits/stdc++.h>
#include <gtest/gtest.h>

using namespace std;

class Solution {
 public:
  int lengthOfLastWord(string s) {
    int n = s.size();
    while (s[--n] == ' ');
    for (auto i{n}; i >= 0; i--)
      if (s[i] == ' ') return n - i;
    return n + 1;
  }
};

TEST(SolutionTest, Test1) {
  Solution solution;
  EXPECT_EQ(5, solution.lengthOfLastWord("Hello World"));
}

TEST(SolutionTest, Test2) {
  Solution solution;
  EXPECT_EQ(4, solution.lengthOfLastWord("   fly me   to   the moon  "));
}

TEST(SolutionTest, Test3) {
  Solution solution;
  EXPECT_EQ(6, solution.lengthOfLastWord("luffy is still joyboy"));
}
