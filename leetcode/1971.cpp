#include <bits/stdc++.h>
#include <gtest/gtest.h>

using namespace std;

class Solution {
 public:
  bool validPath(int n, vector<vector<int>>& edges, int source,
                 int destination) {
    vector<vector<int>> adj(n);
    for (const auto edge : edges) {
      adj[edge[0]].emplace_back(edge[1]);
      adj[edge[1]].emplace_back(edge[0]);
    }

    queue<int> q;
    unordered_set<int> visited;

    q.emplace(source);

    while (!q.empty()) {
      auto node = q.front();
      q.pop();
      if (node == destination) return true;
      for (const auto next_node : adj[node]) {
        if (!visited.contains(next_node)) {
          q.emplace(next_node);
          visited.insert(next_node);
        }
      }
    }

    return false;
  }
};

TEST(SolutionTest, Test1) {
  Solution solution;
  vector<vector<int>> edges{{0, 1}, {1, 2}, {2, 0}};
  EXPECT_TRUE(solution.validPath(3, edges, 0, 2));
}

TEST(SolutionTest, Test2) {
  Solution solution;
  vector<vector<int>> edges{{0, 1}, {0, 2}, {3, 5}, {5, 4}, {4, 3}};
  EXPECT_FALSE(solution.validPath(6, edges, 0, 5));
}
