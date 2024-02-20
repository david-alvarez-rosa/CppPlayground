#include "bits/stdc++.h"
#include <gtest/gtest.h>
using namespace std;

class Solution {
public:
  int missingNumber(vector<int> &nums) {
    auto n{nums.size()};
    vector<bool> found(n + 1, false);
    for (const auto num : nums) found[num] = true;
    return find(found.cbegin(), found.cend(), false) - found.cbegin();
  }
};

TEST(SolutionTest, Test1) {
  Solution solution;
  vector<int> input{3, 0, 1};
  EXPECT_EQ(solution.missingNumber(input), 2);
}

TEST(SolutionTest, Test2) {
  Solution solution;
  vector<int> input{0, 1};
  EXPECT_EQ(solution.missingNumber(input), 2);
}

TEST(SolutionTest, Test3) {
  Solution solution;
  vector<int> input{9, 6, 4, 2, 3, 5, 7, 0, 1};
  EXPECT_EQ(solution.missingNumber(input), 8);
}
