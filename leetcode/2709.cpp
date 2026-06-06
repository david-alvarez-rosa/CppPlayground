#include <bits/stdc++.h>
#include <gtest/gtest.h>

using namespace std;

class Solution {
 public:
  bool canTraverseAllPairs(vector<int>& nums) {
    auto n{nums.size()};
    vector<vector<int>> adj(n);
    for (size_t i{0}; i < n; i++) {
      for (size_t j{i + 1}; j < n; j++) {
        if (gcd(nums[i], nums[j]) > 1) {
          adj[i].emplace_back(j);
          adj[j].emplace_back(i);
        }
      }
    }

    unordered_set<int> visited;
    queue<int> q;

    q.push(0);
    visited.insert(0);

    while (!q.empty()) {
      auto node = q.front();
      q.pop();
      for (const auto next_node : adj[node]) {
        if (!visited.contains(next_node)) {
          q.push(next_node);
          visited.insert(next_node);
        }
      }
    }

    return visited.size() == n;
  }

  int gcd(int a, int b) {
    if (b > a) return gcd(b, a);
    if (a % b == 0) return b;
    return gcd(b, a % b);
  }
};

TEST(SolutionTest, gdc) {
  Solution solution;
  EXPECT_EQ(solution.gcd(2, 3), 1);
  EXPECT_EQ(solution.gcd(2, 2 * 2 * 2), 2);
  EXPECT_EQ(solution.gcd(2 * 3, 3 * 5), 3);
  EXPECT_EQ(solution.gcd(2 * 3 * 5 * 5 * 7, 3 * 5 * 7), 3 * 5 * 7);
  EXPECT_EQ(solution.gcd(1, 8), 1);
  EXPECT_EQ(solution.gcd(28, 39), 1);
}

TEST(SolutionTest, Test1) {
  Solution solution;
  vector<int> nums{2, 3, 6};
  EXPECT_TRUE(solution.canTraverseAllPairs(nums));
}

TEST(SolutionTest, Test2) {
  Solution solution;
  vector<int> nums{3, 9, 5};
  EXPECT_FALSE(solution.canTraverseAllPairs(nums));
}

TEST(SolutionTest, Test3) {
  Solution solution;
  vector<int> nums{4, 3, 12, 8};
  EXPECT_TRUE(solution.canTraverseAllPairs(nums));
}

TEST(SolutionTest, Test772) {
  Solution solution;
  vector<int> nums{28, 39};
  EXPECT_FALSE(solution.canTraverseAllPairs(nums));
}
