#include "bits/stdc++.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
using namespace std;

class Solution {
public:
  int lengthOfLastWord(string s) {
    int n = s.size();
    while (n--) {
      if (s[n] != ' ')
        break;
    }
    n++;
    for (auto i{n - 1}; i >= 0; i--) {
      if (s[i] == ' ')
        return n - i - 1;
    }
    return n;
  }
};

TEST(SolutionTest, Test1) {
  Solution solution;
  auto actual_sol = solution.lengthOfLastWord("Hello World");
  EXPECT_EQ(actual_sol, 5);
}

TEST(SolutionTest, Test2) {
  Solution solution;
  auto actual_sol = solution.lengthOfLastWord("   fly me   to   the moon  ");
  EXPECT_EQ(actual_sol, 4);
}

TEST(SolutionTest, Test3) {
  Solution solution;
  auto actual_sol = solution.lengthOfLastWord("luffy is still joyboy");
  EXPECT_EQ(actual_sol, 6);
}
