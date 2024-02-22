#include "bits/stdc++.h"
#include <gtest/gtest.h>
using namespace std;

class Solution {
public:
  int findJudge(int n, vector<vector<int>> &trust) {
    vector<int> trust_count(n + 1, 0);
    vector<int> trusted_count(n + 1, 0);
    for (const auto trust_relation : trust) {
      assert(trust_relation.size() == 2);
      auto a{trust_relation[0]}, b{trust_relation[1]};
      trust_count[a]++;
      trusted_count[b]++;
    }
    for (int i{1}; i < n + 1; i++) {
      if (trust_count[i] == 0 && trusted_count[i] == n - 1) return i;
    }
    return -1;
  }
};

TEST(SolutionTest, Test1) {
  Solution solution;
  vector<vector<int>> input{{1, 2}};
  EXPECT_EQ(solution.findJudge(2, input), 2);
}

TEST(SolutionTest, Test2) {
  Solution solution;
  vector<vector<int>> input{{1, 3}, {2, 3}};
  EXPECT_EQ(solution.findJudge(3, input), 3);
}

TEST(SolutionTest, Test3) {
  Solution solution;
  vector<vector<int>> input{{1, 3}, {2, 3}, {3, 1}};
  EXPECT_EQ(solution.findJudge(3, input), -1);
}
