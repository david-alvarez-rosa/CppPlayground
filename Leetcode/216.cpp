#include <bits/stdc++.h>
#include <gtest/gtest.h>

using namespace std;

class Solution {
 public:
  vector<vector<int>> combinationSum3(int k, int n, vector<int> curr = {},
                                      int foo = 1) {
    if (!curr.empty() && accumulate(curr.cbegin(), curr.cend(), 0) == n &&
        curr.size() == k)
      return {curr};
    if (foo > 9) return {};

    auto ans = combinationSum3(k, n, curr, foo + 1);
    curr.push_back(foo);
    auto tmp2 = combinationSum3(k, n, curr, foo + 1);
    for (const auto tmp : tmp2) {
      ans.push_back(tmp);
    }

    return ans;
  }
};

TEST(SolutionTest, Test1) {
  Solution solution;
  vector<vector<int>> expected = {{1, 2, 4}};
  EXPECT_EQ(solution.combinationSum3(3, 7), expected);
}

TEST(SolutionTest, Test2) {
  Solution solution;
  vector<vector<int>> expected = {{2, 3, 4}, {1, 3, 5}, {1, 2, 6}};
  EXPECT_EQ(solution.combinationSum3(3, 9), expected);
}

TEST(SolutionTest, Test3) {
  Solution solution;
  vector<vector<int>> expected = {};
  EXPECT_EQ(solution.combinationSum3(4, 1), expected);
}
