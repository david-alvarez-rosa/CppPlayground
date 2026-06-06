#include <bits/stdc++.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace std;
using namespace testing;
using P = pair<int, int>;

class Solution {
 public:
  vector<int> topKFrequent(vector<int>& nums, int k) {
    unordered_map<int, int> fqs;
    for (const auto num : nums) fqs[num]++;

    priority_queue<P, vector<P>, greater<P>> pq;
    for (const auto [num, fq] : fqs) {
      if (pq.size() < k || fq > pq.top().first) {
        if (pq.size() == k) pq.pop();
        pq.push({fq, num});
      }
    }

    vector<int> ans(k);
    while (k--) {
      auto [_, num] = pq.top();
      pq.pop();
      ans[k] = num;
    }

    return ans;
  }
};

TEST(SolutionTest, Test1) {
  Solution solution;
  vector<int> nums{1, 1, 1, 2, 2, 3};
  EXPECT_THAT(solution.topKFrequent(nums, 2), UnorderedElementsAre(1, 2));
}

TEST(SolutionTest, Test2) {
  Solution solution;
  vector<int> nums{1};
  EXPECT_THAT(solution.topKFrequent(nums, 1), UnorderedElementsAre(1));
}

TEST(SolutionTest, Test5) {
  Solution solution;
  vector<int> nums{3, 0, 1, 0};
  EXPECT_THAT(solution.topKFrequent(nums, 1), UnorderedElementsAre(0));
}

TEST(SolutionTest, Test9) {
  Solution solution;
  vector<int> nums{1, 2};
  EXPECT_THAT(solution.topKFrequent(nums, 2), UnorderedElementsAre(1, 2));
}

TEST(SolutionTest, Test11) {
  Solution solution;
  vector<int> nums{-1, 1, 4, -4, 3, 5, 4, -2, 3, -1};
  EXPECT_THAT(solution.topKFrequent(nums, 3), UnorderedElementsAre(3, 4, -1));
}
