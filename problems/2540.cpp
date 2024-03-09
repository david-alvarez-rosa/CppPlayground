#include <bits/stdc++.h>
#include <gtest/gtest.h>

using namespace std;

class Solution {
 public:
  int getCommon(vector<int>& nums1, vector<int>& nums2) {
    size_t i1{0}, i2{0};
    while (i1 < nums1.size() && i2 < nums2.size()) {
      if (nums1[i1] == nums2[i2]) return nums1[i1];
      if (nums1[i1] < nums2[i2])
        i1++;
      else
        i2++;
    }
    return -1;
  }
};

TEST(SolutionTest, Test1) {
  Solution solution;
  vector<int> nums1{1, 2, 3};
  vector<int> nums2{2, 4};
  EXPECT_EQ(2, solution.getCommon(nums1, nums2));
}

TEST(SolutionTest, Test2) {
  Solution solution;
  vector<int> nums1{1, 2, 3, 6};
  vector<int> nums2{2, 3, 4, 5};
  EXPECT_EQ(2, solution.getCommon(nums1, nums2));
}
