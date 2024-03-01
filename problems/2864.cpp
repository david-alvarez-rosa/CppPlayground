#include <bits/stdc++.h>
#include <gtest/gtest.h>

#include <algorithm>

using namespace std;

class Solution {
 public:
  string maximumOddBinaryNumber(string s) {
    size_t count_ones{0}, n{s.length()};

    for (auto c : s)
      if (c == '1') count_ones++;

    for (size_t i{0}; i < count_ones - 1; i++) s[i] = '1';
    for (size_t i{count_ones - 1}; i < n - 1; i++) s[i] = '0';
    s[n - 1] = '1';

    return s;
  }
};

TEST(SolutionTest, Test1) {
  Solution solution;
  EXPECT_EQ("001", solution.maximumOddBinaryNumber("010"));
}

TEST(SolutionTest, Test2) {
  Solution solution;
  EXPECT_EQ("1001", solution.maximumOddBinaryNumber("0101"));
}
