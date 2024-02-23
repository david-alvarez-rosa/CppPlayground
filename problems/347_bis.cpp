#include <bits/stdc++.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace std;

class Solution {
 public:
  vector<int> topKFrequent(vector<int>& nums, int k) {
    unordered_map<int, int> fqs;
    for (const auto num : nums) fqs[num]++;

    vector<pair<int, int>> foo;
    foo.reserve(fqs.size());  // [(fq, num)]
    for (const auto [num, fq] : fqs) foo.push_back({fq, num});

    sortFirstKElements(foo, k, 0, fqs.size() - 1);

    vector<int> ans;
    while (k--) ans.push_back(foo[k].second);

    return ans;
  }

 private:
  int partition(vector<pair<int, int>>& v, int l, int r, int pivot) {
    int p{l};
    for (int i{l}; i < r; i++) {
      if (v[i].first > pivot) {
        swap(v[i], v[p]);
        p++;
      }
    }
    swap(v[p], v[r]);
    return p;
  }

  void sortFirstKElements(vector<pair<int, int>>& v, int k, int l, int r) {
    if (k < 1 || l >= r) return;
    if (k > r - l + 1) k = l - r + 1;
    auto pivot = v[r].first;
    auto p = partition(v, l, r, pivot);
    sortFirstKElements(v, k, l, p - 1);
    sortFirstKElements(v, k - (p - 1 - l), p + 1, r);
  }
};

TEST(SolutionTest, Test1) {
  Solution solution;
  vector<int> nums{1, 1, 1, 2, 2, 3};
  EXPECT_THAT(solution.topKFrequent(nums, 2),
              testing::UnorderedElementsAre(1, 2));
}

TEST(SolutionTest, Test2) {
  Solution solution;
  vector<int> nums{1};
  EXPECT_THAT(solution.topKFrequent(nums, 1), testing::UnorderedElementsAre(1));
}

TEST(SolutionTest, Test5) {
  Solution solution;
  vector<int> nums{3, 0, 1, 0};
  EXPECT_THAT(solution.topKFrequent(nums, 1), testing::UnorderedElementsAre(0));
}

TEST(SolutionTest, Test9) {
  Solution solution;
  vector<int> nums{1, 2};
  EXPECT_THAT(solution.topKFrequent(nums, 2),
              testing::UnorderedElementsAre(1, 2));
}

TEST(SolutionTest, Test11) {
  Solution solution;
  vector<int> nums{-1, 1, 4, -4, 3, 5, 4, -2, 3, -1};
  EXPECT_THAT(solution.topKFrequent(nums, 3),
              testing::UnorderedElementsAre(3, 4, -1));
}
