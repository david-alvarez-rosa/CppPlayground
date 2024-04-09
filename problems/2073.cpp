#include <bits/stdc++.h>
#include <gtest/gtest.h>

using namespace std;

class Solution {
 public:
  int timeRequiredToBuy(vector<int>& tickets, int k) {
    int ans{0};
    for (int i{0}; i <= k; i++) ans += min(tickets[k], tickets[i]);
    for (int i{k + 1}; i < tickets.size(); i++)
      ans += min(tickets[k] - 1, tickets[i]);
    return ans;
  }
};

TEST(SolutionTest, Test1) {
  Solution solution;
  vector<int> tickets{{2, 3, 2}};
  EXPECT_EQ(6, solution.timeRequiredToBuy(tickets, 2));
}

TEST(SolutionTest, Test2) {
  Solution solution;
  vector<int> tickets{{5, 1, 1, 1}};
  EXPECT_EQ(8, solution.timeRequiredToBuy(tickets, 0));
}

TEST(SolutionTest, Test3) {
  Solution solution;
  vector<int> tickets{{84, 49, 5, 24, 70, 77, 87, 8}};
  EXPECT_EQ(154, solution.timeRequiredToBuy(tickets, 3));
}
