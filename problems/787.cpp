#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "bits/stdc++.h"

using namespace std;

class Solution {
 public:
  int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst,
                        int k) {
    vector<vector<pair<int, int>>> adj(n);  // [from](to, weight)
    for (const auto flight : flights) {
      assert(flight.size() == 3);
      auto from{flight[0]}, to{flight[1]}, weight{flight[2]};
      adj[from].push_back({to, weight});
    }

    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>,
                   greater<tuple<int, int, int>>>
        pq;  // (cost, stops, node)
    vector<int> distances(n, INT_MAX);
    pq.push({0, 0, src});

    while (!pq.empty()) {
      auto [cost, stops, city] = pq.top();
      pq.pop();
      if (city == dst) {
        return cost;
      }
      if (distances[city] < stops) continue;
      distances[city] = stops;
      for (const auto [next_city, flight_cost] : adj[city]) {
        if (stops <= k) {
          pq.push({cost + flight_cost, stops + 1, next_city});
        }
      }
    }

    return -1;
  }
};

TEST(SolutionTest, Test1) {
  Solution solution;
  vector<vector<int>> flights = {
      {0, 1, 100}, {1, 2, 100}, {2, 0, 100}, {1, 3, 600}, {2, 3, 200},
  };
  EXPECT_EQ(700, solution.findCheapestPrice(4, flights, 0, 3, 1));
}

TEST(SolutionTest, Test2) {
  Solution solution;
  vector<vector<int>> flights = {
      {0, 1, 100},
      {1, 2, 100},
      {0, 2, 500},
  };
  EXPECT_EQ(200, solution.findCheapestPrice(3, flights, 0, 2, 1));
}

TEST(SolutionTest, Test3) {
  Solution solution;
  vector<vector<int>> flights = {
      {0, 1, 100},
      {1, 2, 100},
      {0, 2, 500},
  };
  EXPECT_EQ(500, solution.findCheapestPrice(3, flights, 0, 2, 0));
}

TEST(SolutionTest, Test11) {
  Solution solution;
  vector<vector<int>> flights = {
      {0, 3, 3}, {3, 4, 3},   {4, 1, 3},  {0, 5, 1},   {5, 1, 100},
      {0, 6, 2}, {6, 1, 100}, {0, 7, 1},  {7, 8, 1},   {8, 9, 1},
      {9, 1, 1}, {1, 10, 1},  {10, 2, 1}, {1, 2, 100},
  };
  EXPECT_EQ(11, solution.findCheapestPrice(11, flights, 0, 2, 4));
}
