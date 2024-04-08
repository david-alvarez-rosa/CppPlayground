#include <bits/stdc++.h>
#include <gtest/gtest.h>

using namespace std;

class Solution {
 public:
  int countStudents(vector<int>& students, vector<int>& sandwiches) {
    int sandwitch{0}, student{-1}, count{0};
    auto n = sandwiches.size();

    while (sandwitch < sandwiches.size() && ++student < students.size() &&
           count++ < n) {
      if (students[student] == sandwiches[sandwitch]) {
        sandwitch++;
        n = sandwiches.size() - sandwitch + 1;
        count = 0;
      } else
        students.emplace_back(students[student]);
    }

    return sandwiches.size() - sandwitch;
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
