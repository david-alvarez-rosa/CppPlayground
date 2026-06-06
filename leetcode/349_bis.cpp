#include <bits/stdc++.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace std;
using namespace testing;

class Solution {
 public:
  vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
    set<int> set1(nums1.cbegin(), nums1.cend());
    set<int> set2(nums2.cbegin(), nums2.cend());

    vector<int> ans;
    set_intersection(set1.cbegin(), set1.cend(), set2.cbegin(), set2.cend(),
                     back_inserter(ans));
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
