#include <bits/stdc++.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace std;
using namespace testing;

class Solution {
 public:
  vector<int> successfulPairs(vector<int>& spells, vector<int>& potions,
                              long long success) {
    const auto n{spells.size()}, m{potions.size()};
    sort(potions.begin(), potions.end());
    vector<int> ans(n);
    for (size_t i{0}; i < n; i++) {
      int left = 0, right = m - 1;
      while (left <= right) {
        int mid = (left + right) / 2;
        auto product = (long long)spells[i] * potions[mid];
        if (product >= success)
          right = mid - 1;
        else
          left = mid + 1;
      }
      ans[i] = m - left;
    }
    return ans;
  }
};

TEST(SolutionTest, Test1) {
  Solution solution;
  vector<int> spells{5, 1, 3};
  vector<int> potions{1, 2, 3, 4, 5};
  EXPECT_THAT(solution.successfulPairs(spells, potions, 7),
              ElementsAre(4, 0, 3));
}

TEST(SolutionTest, Test2) {
  Solution solution;
  vector<int> spells{3, 1, 2};
  vector<int> potions{8, 5, 8};
  EXPECT_THAT(solution.successfulPairs(spells, potions, 16),
              ElementsAre(2, 0, 2));
}
