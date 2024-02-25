#include <bits/stdc++.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace std;
using namespace testing;

class Solution {
 public:
  vector<int> findAllPeople(int n, vector<vector<int>>& meetings,
                            int firstPerson) {
    /*
      for each_time
        I need meetings graph (adjacency matrix) at that time
        expand secret by traversing graph (bfs, dfs, union-find)
        save who know the secret
      endfor

      return array of people that know the secret
     */

    map<int, vector<vector<int>>> adjs;  // (time, adj at time)
    for (const auto& meeting : meetings) {
      assert(meeting.size() == 3);
      auto person_x = meeting[0];
      auto person_y = meeting[1];
      auto meeting_time = meeting[2];
      if (!adjs.contains(meeting_time))
        adjs[meeting_time] = vector<vector<int>>(n);
      adjs[meeting_time][person_x].emplace_back(person_y);
      adjs[meeting_time][person_y].emplace_back(person_x);
    }

    vector<bool> secret(n, false);
    secret[0] = true;
    secret[firstPerson] = true;

    for (const auto& [time, adj] : adjs) {
      unordered_set<int> visited;
      for (size_t i{0}; i < n; i++) {
        if (!visited.contains(i) && secret[i]) {
          // worth expanding
          queue<int> q;
          q.push(i);
          visited.insert(i);
          while (!q.empty()) {
            auto node = q.front();
            q.pop();
            for (const auto next_node : adj[node]) {
              if (!visited.contains(next_node)) {
                q.push(next_node);
                visited.insert(next_node);
                secret[next_node] = true;
              }
            }
          }
        }
      }
    }

    vector<int> ans;
    for (size_t i{0}; i < n; i++)
      if (secret[i]) ans.emplace_back(i);

    return ans;
  }
};

TEST(SolutionTest, Test1) {
  Solution solution;
  vector<vector<int>> meetings{{1, 2, 5}, {2, 3, 8}, {1, 5, 10}};
  EXPECT_THAT(solution.findAllPeople(6, meetings, 1),
              UnorderedElementsAre(0, 1, 2, 3, 5));
}

TEST(SolutionTest, Test2) {
  Solution solution;
  vector<vector<int>> meetings{{3, 1, 3}, {1, 2, 2}, {0, 3, 3}};
  EXPECT_THAT(solution.findAllPeople(4, meetings, 3),
              UnorderedElementsAre(0, 1, 3));
}

TEST(SolutionTest, Test3) {
  Solution solution;
  vector<vector<int>> meetings{{3, 4, 2}, {1, 2, 1}, {2, 3, 1}};
  EXPECT_THAT(solution.findAllPeople(5, meetings, 1),
              UnorderedElementsAre(0, 1, 2, 3, 4));
}
