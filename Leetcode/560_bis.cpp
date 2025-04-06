#include <gtest/gtest.h>

#include <cstddef>
#include <unordered_map>
#include <vector>

class Solution {
 public:
  int subarraySum(std::vector<int>& nums, int k, int start = 0) {
    auto sum = 0, ans{0};
    std::unordered_map<int, int> fqs;
    fqs[0] = 1;
    for (std::size_t i = 0; i < nums.size(); ++i) {
      sum += nums[i];
      if (fqs.contains(sum - k)) {
        ans += fqs[sum - k];
      }
      ++fqs[sum];
    }
    return ans;
  }
};

TEST(SolutionTest, Test1) {
  Solution solution;
  std::vector<int> nums{1, 1, 1};
  EXPECT_EQ(2, solution.subarraySum(nums, 2));
}

TEST(SolutionTest, Test2) {
  Solution solution;
  std::vector<int> nums{1, 2, 3};
  EXPECT_EQ(2, solution.subarraySum(nums, 3));
}
