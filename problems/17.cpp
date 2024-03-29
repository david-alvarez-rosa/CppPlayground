#include <bits/stdc++.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace std;
using namespace testing;

class Solution {
 public:
  vector<string> letterCombinations(string digits, int start = 0) {
    if (digits.size() == 0) return {};
    if (start == digits.size() - 1) return mp_[digits[start] - '2'];

    vector<string> ans;
    for (const auto letter : mp_[digits[start] - '2'])
      for (const auto foo : letterCombinations(digits, start + 1))
        ans.emplace_back(string(letter) + foo);

    return ans;
  }

 private:
  const vector<vector<string>> mp_ = {{"a", "b", "c"}, {"d", "e", "f"},
                                      {"g", "h", "i"}, {"j", "k", "l"},
                                      {"m", "n", "o"}, {"p", "q", "r", "s"},
                                      {"t", "u", "v"}, {"w", "x", "y", "z"}};
};

TEST(SolutionTest, Test1) {
  Solution solution;
  string digits{"23"};
  EXPECT_THAT(solution.letterCombinations(digits),
              UnorderedElementsAre("ad", "ae", "af", "bd", "be", "bf", "cd",
                                   "ce", "cf"));
}

TEST(SolutionTest, Test2) {
  Solution solution;
  string digits{""};
  EXPECT_THAT(solution.letterCombinations(digits), UnorderedElementsAre());
}

TEST(SolutionTest, Test3) {
  Solution solution;
  string digits{"2"};
  EXPECT_THAT(solution.letterCombinations(digits),
              UnorderedElementsAre("a", "b", "c"));
}

TEST(SolutionTest, Test22) {
  Solution solution;
  string digits{"9"};
  EXPECT_THAT(solution.letterCombinations(digits),
              UnorderedElementsAre("w", "x", "y", "z"));
}
