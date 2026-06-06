#include <bits/stdc++.h>
#include <gtest/gtest.h>

using namespace std;

class Solution {
 public:
  int countStudents(vector<int>& students, vector<int>& sandwiches) {
    vector<int> counts(2, 0);
    for (const auto student : students) counts[student]++;

    auto remaining{sandwiches.size()};
    for (const auto sandwich : sandwiches) {
      if (counts[sandwich] == 0 || remaining == 0) break;
      counts[sandwich]--;
      remaining--;
    }

    return remaining;
  }
};

TEST(SolutionTest, Test1) {
  Solution solution;
  vector<int> students{{1, 1, 0, 0}};
  vector<int> sandwiches{{0, 1, 0, 1}};
  EXPECT_EQ(0, solution.countStudents(students, sandwiches));
}

TEST(SolutionTest, Test2) {
  Solution solution;
  vector<int> students{{1, 1, 1, 0, 0, 1}};
  vector<int> sandwiches{{1, 0, 0, 0, 1, 1}};
  EXPECT_EQ(3, solution.countStudents(students, sandwiches));
}
