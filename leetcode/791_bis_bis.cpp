#include <bits/stdc++.h>
#include <gtest/gtest.h>

using namespace std;

class Solution {
 public:
  string customSortString(string order, string s) {
    unordered_map<char, int> fqs;
    for (const auto c : s) fqs[c]++;

    string ans;
    ans.reserve(order.length());
    for (const auto c : order)
      if (fqs.contains(c)) {
        ans.append(fqs[c], c);
        fqs.erase(c);
      }

    for (const auto [c, fq] : fqs) ans.append(fq, c);

    return ans;
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
