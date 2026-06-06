#include <bits/stdc++.h>
#include <gtest/gtest.h>

using namespace std;

class Solution {
 public:
  bool checkValidString(string s) {
    for (int i{0}, count{0}, asterisk{0}; i < s.size(); i++) {
      if (s[i] == '*') {
        asterisk++;
        continue;
      }
      count += s[i] == '(' ? -1 : 1;
      if (count > asterisk) return false;
    }

    for (int i{0}, count{0}, asterisk{0}; i < s.size(); i++) {
      if (s[s.size() - 1 - i] == '*') {
        asterisk++;
        continue;
      }
      count += s[s.size() - 1 - i] == '(' ? 1 : -1;
      if (count > asterisk) return false;
    }

    return true;
  }
};

TEST(SolutionTest, Test1) {
  Solution solution;
  EXPECT_TRUE(solution.checkValidString("()"));
}

TEST(SolutionTest, Test2) {
  Solution solution;
  EXPECT_TRUE(solution.checkValidString("(*)"));
}

TEST(SolutionTest, Test3) {
  Solution solution;
  EXPECT_TRUE(solution.checkValidString("(*))"));
}

TEST(SolutionTest, Test4) {
  Solution solution;
  EXPECT_FALSE(solution.checkValidString("())"));
}

TEST(SolutionTest, Test5) {
  Solution solution;
  EXPECT_FALSE(solution.checkValidString("(()"));
}
