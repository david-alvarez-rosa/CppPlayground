#include <bits/stdc++.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace std;
using namespace testing;

class Solution {
 public:
  vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
    sort(nums1.begin(), nums1.end());
    sort(nums2.begin(), nums2.end());
    vector<int> ans;
    ans.reserve(min(nums1.size(), nums2.size()));
    size_t i1{0}, i2{0};
    while (i1 < nums1.size() && i2 < nums2.size()) {
      if (nums1[i1] == nums2[i2]) {
        if (ans.size() == 0 || ans[ans.size() - 1] != nums1[i1])
          ans.emplace_back(nums1[i1]);
        i1++;
        i2++;
      } else if (nums1[i1] < nums2[i2])
        i1++;
      else
        i2++;
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
