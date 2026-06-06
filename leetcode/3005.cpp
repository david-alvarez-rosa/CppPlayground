#include <bits/stdc++.h>
#include <gtest/gtest.h>

using namespace std;

class Solution {
 public:
  int maxFrequencyElements(vector<int>& nums) {
    unordered_map<int, int> fqs;
    for (const auto num : nums) fqs[num]++;

    vector<int> fqs_raw;
    fqs_raw.reserve(fqs.size());
    for (const auto [num, fq] : fqs) fqs_raw.emplace_back(fq);

    int max_fq = *max_element(fqs_raw.cbegin(), fqs_raw.cend());

    int ans{0};
    for (const auto fq : fqs_raw)
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
