#include <bits/stdc++.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace std;

class Solution {
 public:
  vector<int> topKFrequent(vector<int>& nums, int k) {
    unordered_map<int, int> fqs;
    for (const auto num : nums) {
      fqs[num]++;
    }

    vector<int> fq_values;
    fq_values.reserve(fqs.size());
    for (const auto [num, fq] : fqs) fq_values.emplace_back(fq);

    sort(fq_values.begin(), fq_values.end());
    int fq_k = fq_values[fq_values.size() - k];

    vector<int> ans;
    ans.reserve(k);
    for (const auto [num, fq] : fqs) {
      if (fq >= fq_k) {
        ans.emplace_back(num);
      }
    }

    return ans;
  }
};

TEST(SolutionTest, Test1) {
  Solution solution;
  vector<int> input{1, 1, 1, 2, 2, 3};
  EXPECT_THAT(solution.topKFrequent(input, 2),
              testing::UnorderedElementsAre(1, 2));
}

TEST(SolutionTest, Test2) {
  Solution solution;
  vector<int> input{1};
  EXPECT_THAT(solution.topKFrequent(input, 1),
              testing::UnorderedElementsAre(1));
}

TEST(SolutionTest, Test9) {
  Solution solution;
  vector<int> input{1, 2};
  EXPECT_THAT(solution.topKFrequent(input, 2),
              testing::UnorderedElementsAre(1, 2));
}
