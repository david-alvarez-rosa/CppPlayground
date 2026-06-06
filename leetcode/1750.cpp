#include <bits/stdc++.h>
#include <gtest/gtest.h>

using namespace std;

class Solution {
 public:
  int minimumLength(string s) {
    size_t left{0}, right{s.size() - 1};
    while (left < right) {
      if (s[left] == s[right]) {
        auto to_remove = s[left];
        while (left <= right && s[left] == to_remove) {
          left++;
        }
        while (left <= right && s[right] == to_remove) {
          right--;
        }
      } else {
        return right - left + 1;
      }
    }
    return right - left + 1;
  }
};

TEST(SolutionTest, Test1) {
  Solution solution;
  EXPECT_EQ(2, solution.minimumLength("ca"));
}

TEST(SolutionTest, Test2) {
  Solution solution;
  EXPECT_EQ(0, solution.minimumLength("cabaabac"));
}

TEST(SolutionTest, Test3) {
  Solution solution;
  EXPECT_EQ(3, solution.minimumLength("aabccabba"));
}
