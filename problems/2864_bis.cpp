#include <bits/stdc++.h>
#include <gtest/gtest.h>

using namespace std;

class Solution {
 public:
  string maximumOddBinaryNumber(string s) {
    auto n{s.length()};

    auto count_ones =
        count_if(s.cbegin(), s.cend(), [](const auto c) { return c == '1'; });

    for (size_t i{0}; i < count_ones - 1; i++) s[i] = '1';
    for (size_t i = count_ones - 1; i < n - 1; i++) s[i] = '0';
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
