#include <bits/stdc++.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace std;
using namespace testing;

class Solution {
 public:
  vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
    unordered_set<int> us;
    for (const auto num1 : nums1) us.insert(num1);

    vector<int> ans;
    ans.reserve(min(nums1.size(), nums2.size()));
    for (const auto num2 : nums2)
      if (us.contains(num2)) {
        ans.emplace_back(num2);
        us.erase(num2);
      }
    return ans;
  }
};

TEST(SolutionTest, Test1) {
  Solution solution;
  vector<int> nums1{1, 2, 2, 1};
  vector<int> nums2{2, 2};
  EXPECT_THAT(solution.intersection(nums1, nums2), UnorderedElementsAre(2));
}

TEST(SolutionTest, Test2) {
  Solution solution;
  vector<int> nums1{4, 9, 5};
  vector<int> nums2{9, 4, 9, 8, 4};
  EXPECT_THAT(solution.intersection(nums1, nums2), UnorderedElementsAre(4, 9));
}
