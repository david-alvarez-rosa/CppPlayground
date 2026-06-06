#include <bits/stdc++.h>
#include <gtest/gtest.h>

using namespace std;

class Solution {
 public:
  vector<int> finalPrices(vector<int>& prices) {
    for (int i = 0; i < prices.size(); ++i) {
      for (int j = i + 1; j < prices.size(); ++j) {
        if (prices[j] <= prices[i]) {
          prices[i] -= prices[j];
          break;
        }
      }
    }
    return prices;
  }
};

TEST(SolutionTest, Test1) {
  Solution solution;
  vector<int> prices = {8, 4, 6, 2, 3};
  vector<int> ans = {4, 2, 4, 2, 3};
  EXPECT_EQ(ans, solution.finalPrices(prices));
}

TEST(SolutionTest, Test2) {
  Solution solution;
  vector<int> prices = {1, 2, 3, 4, 5};
  vector<int> ans = {1, 2, 3, 4, 5};
  EXPECT_EQ(ans, solution.finalPrices(prices));
}

TEST(SolutionTest, Test3) {
  Solution solution;
  vector<int> prices = {10, 1, 1, 6};
  vector<int> ans = {9, 0, 1, 6};
  EXPECT_EQ(ans, solution.finalPrices(prices));
}
