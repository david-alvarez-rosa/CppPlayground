#include <bits/stdc++.h>
#include <gtest/gtest.h>

using namespace std;

class Solution {
 public:
  int maxFrequencyElements(vector<int>& nums) {
    unordered_map<int, int> fqs;
    for (const auto num : nums) fqs[num]++;

    int max_fq{0};
    for (const auto [num, fq] : fqs) max_fq = max(max_fq, fq);

    int ans{0};
    for (const auto [_, fq] : fqs)
      if (fq == max_fq) ans++;

    return ans * max_fq;
  }
};

TEST(SolutionTest, Test1) {
  Solution solution;
  vector<int> nums{1, 2, 2, 3, 1, 4};
  EXPECT_EQ(4, solution.maxFrequencyElements(nums));
}

TEST(SolutionTest, Test2) {
  Solution solution;
  vector<int> nums{1, 2, 3, 4, 5};
  EXPECT_EQ(5, solution.maxFrequencyElements(nums));
}
