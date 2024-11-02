#include <bits/stdc++.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace std;
using namespace testing;

class Solution {
 public:
  vector<int> deckRevealedIncreasing(vector<int>& deck) {
    sort(deck.begin(), deck.end());

    queue<int> q;
    q.emplace(*deck.crbegin());
    for (auto it = deck.crbegin() + 1; it != deck.crend(); it++) {
      auto front_card = q.front();
      q.pop();
      q.emplace(front_card);
      q.emplace(*it);
    }

    vector<int> ans;
    while (!q.empty()) {
      ans.emplace_back(q.front());
      q.pop();
    }

    reverse(ans.begin(), ans.end());

    return ans;
  }
};

TEST(SolutionTest, Test1) {
  Solution solution;
  vector<int> deck{{17, 13, 11, 2, 3, 5, 7}};
  EXPECT_THAT(solution.deckRevealedIncreasing(deck),
              ElementsAre(2, 13, 3, 11, 5, 17, 7));
}

TEST(SolutionTest, Test2) {
  Solution solution;
  vector<int> deck{{1, 1000}};
  EXPECT_THAT(solution.deckRevealedIncreasing(deck), ElementsAre(1, 1000));
}
