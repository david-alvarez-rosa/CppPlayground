#include <bits/stdc++.h>
#include <gtest/gtest.h>

using namespace std;

class Solution {
 public:
  int minCostClimbingStairs(vector<int>& cost) {
    cost_ = std::move(cost);
    return min(f(0), f(1));
  }

 private:
  int f(int step) {
    if (step > cost_.size()) return INT_MAX;
    if (step == cost_.size()) return 0;
    return cost_[step] + min(f(step + 1), f(step + 2));
  }

  vector<int> cost_;
};

TEST(SolutionTest, Test1) {
  Solution solution;
  vector<int> cost{10, 15, 20};
  EXPECT_EQ(15, solution.minCostClimbingStairs(cost));
}

TEST(SolutionTest, Test2) {
  Solution solution;
  vector<int> cost{1, 100, 1, 1, 1, 100, 1, 1, 100, 1};
  EXPECT_EQ(6, solution.minCostClimbingStairs(cost));
}
