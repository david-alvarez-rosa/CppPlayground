#include <bits/stdc++.h>
#include <gtest/gtest.h>

using namespace std;

class Solution {
 public:
  string customSortString(string order, string s) {
    unordered_map<char, int> mp;
    for (int i{0}; i < order.length(); i++) mp[order[i]] = i;
    sort(s.begin(), s.end(), [&mp](const auto a, const auto b) {
      if (!mp.contains(a)) mp[a] = mp.size();
      if (!mp.contains(b)) mp[b] = mp.size();
      return mp[a] < mp[b];
    });
    return s;
  }
};

TEST(SolutionTest, Test1) {
  Solution solution;
  string order{"cba"};
  string s{"abcd"};
  EXPECT_EQ("cbad", solution.customSortString(order, s));
}

TEST(SolutionTest, Test2) {
  Solution solution;
  string order{"bcafg"};
  string s{"abcd"};
  EXPECT_EQ("bcad", solution.customSortString(order, s));
}

TEST(SolutionTest, Test3) {
  Solution solution;
  string order{"exv"};
  string s{"xwvee"};
  EXPECT_EQ("eexvw", solution.customSortString(order, s));
}
