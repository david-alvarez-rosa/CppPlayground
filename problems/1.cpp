#include <bits/stdc++.h>
#include <gtest/gtest.h>

using namespace std;

class Solution {
 public:
  vector<int> twoSum(vector<int>& nums, int target) {
    for (int i{0}; i < nums.size(); i++) {
      for (int j{i + 1}; j < nums.size(); j++) {
        if (nums[i] + nums[j] == target) {
          return {i, j};
        }
      }
    }
    return {0, 0};
  }
};

TEST(SolutionTest, Test1) {
  Solution solution;
  vector<int> input_1{2, 7, 11, 15};
  auto actual_sol = solution.twoSum(input_1, 9);
  vector<int> expected_sol{0, 1};
  EXPECT_EQ(actual_sol, expected_sol);
}

TEST(SolutionTest, Test2) {
  Solution solution;
  vector<int> input_1{3, 2, 4};
  auto actual_sol = solution.twoSum(input_1, 6);
  vector<int> expected_sol{1, 2};
  EXPECT_EQ(actual_sol, expected_sol);
}

TEST(SolutionTest, Test3) {
  Solution solution;
  vector<int> input_1{3, 3};
  auto actual_sol = solution.twoSum(input_1, 6);
  vector<int> expected_sol{0, 1};
  EXPECT_EQ(actual_sol, expected_sol);
}
