#include <bits/stdc++.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace std;
using namespace testing;

class Solution {
 public:
  vector<string> letterCombinations(string digits, int start = 0) {
    if (digits.empty()) return {};
    vector<string> ans = {""};
    for (const auto digit : digits) {
      vector<string> tmp;
      for (const auto letter : pad_[digit - '2'])
        for (const auto& curr : ans) tmp.push_back(curr + letter);
      ans = tmp;
    }
    return ans;
  }

 private:
  const vector<string> pad_ = {"abc", "def",  "ghi", "jkl",
                               "mno", "pqrs", "tuv", "wxyz"};
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
