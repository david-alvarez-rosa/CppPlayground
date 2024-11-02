#include <bits/stdc++.h>
#include <gtest/gtest.h>

using namespace std;

class Solution {
 public:
  bool validPath(int n, vector<vector<int>>& edges, int source,
                 int destination) {
    for (size_t i{0}; i < n; i++) parents_.emplace_back(i);
    for (const auto e : edges) Union(e[0], e[1]);
    return Find(source) == Find(destination);
  }

 private:
  void Union(int x, int y) {
    auto root_x = Find(x);
    auto root_y = Find(y);
    parents_[root_x] = root_y;
  }

  int Find(int x) {
    auto& parent = parents_[x];
    if (parent == x) return x;
    return parent = Find(parent);
  }

  vector<int> parents_;
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
