#include <bits/stdc++.h>
#include <gtest/gtest.h>

using namespace std;

class Solution {
 public:
  bool isIsomorphic(string s, string t) {
    assert(s.size() == t.size());
    unordered_map<char, char> mp_s, mp_t;
    for (size_t i{0}; i < s.size(); i++) {
      if (mp_s.contains(s[i]) && mp_s[s[i]] != t[i]) return false;
      mp_s[s[i]] = t[i];
      if (mp_t.contains(t[i]) && mp_t[t[i]] != s[i]) return false;
      mp_t[t[i]] = s[i];
    }
    return true;
  }
};

TEST(SolutionTest, Test1) {
  Solution solution;
  EXPECT_TRUE(solution.isIsomorphic("egg", "add"));
}

TEST(SolutionTest, Test2) {
  Solution solution;
  EXPECT_FALSE(solution.isIsomorphic("foo", "bar"));
}

TEST(SolutionTest, Test3) {
  Solution solution;
  EXPECT_TRUE(solution.isIsomorphic("paper", "title"));
}

TEST(SolutionTest, Test36) {
  Solution solution;
  EXPECT_FALSE(solution.isIsomorphic("badc", "baba"));
}
