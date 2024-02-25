#include <bits/stdc++.h>
#include <gtest/gtest.h>

#include <vector>

using namespace std;

namespace {

int gcd(int a, int b) {
  if (b > a) return gcd(b, a);
  if (a % b == 0) return b;
  return gcd(b, a % b);
}

}  // namespace

class Solution {
 public:
  bool canTraverseAllPairs(vector<int>& nums) {
    auto n{nums.size()};
    size_ = vector<int>(n, 1);
    for (size_t i{0}; i < n; i++) parents_.emplace_back(i);
    for (size_t i{0}; i < n; i++)
      for (size_t j{i + 1}; j < n; j++)
        if (gcd(nums[i], nums[j]) > 1) Union(i, j);

    return size_[Find(0)] == n;
  }

 private:
  int Find(int x) {
    auto& parent = parents_[x];
    if (parent == x) return parent;
    return parent = Find(parent);
  }

  void Union(int x, int y) {
    x = Find(x);
    y = Find(y);

    if (x == y) return;

    if (size_[x] < size_[y]) swap(x, y);

    parents_[y] = x;
    size_[x] += size_[y];
  }

  vector<int> parents_;
  vector<int> size_;
};

TEST(SolutionTest, gdc) {
  EXPECT_EQ(gcd(2, 3), 1);
  EXPECT_EQ(gcd(2, 2 * 2 * 2), 2);
  EXPECT_EQ(gcd(2 * 3, 3 * 5), 3);
  EXPECT_EQ(gcd(2 * 3 * 5 * 5 * 7, 3 * 5 * 7), 3 * 5 * 7);
  EXPECT_EQ(gcd(1, 8), 1);
  EXPECT_EQ(gcd(28, 39), 1);
}

TEST(SolutionTest, Test1) {
  Solution solution;
  vector<int> nums{2, 3, 6};
  EXPECT_TRUE(solution.canTraverseAllPairs(nums));
}

TEST(SolutionTest, Test2) {
  Solution solution;
  vector<int> nums{3, 9, 5};
  EXPECT_FALSE(solution.canTraverseAllPairs(nums));
}

TEST(SolutionTest, Test3) {
  Solution solution;
  vector<int> nums{4, 3, 12, 8};
  EXPECT_TRUE(solution.canTraverseAllPairs(nums));
}

TEST(SolutionTest, Test772) {
  Solution solution;
  vector<int> nums{28, 39};
  EXPECT_FALSE(solution.canTraverseAllPairs(nums));
}
