#include <gtest/gtest.h>

#include <vector>

class Solution {
 public:
  static int minOperations(std::vector<int>& nums) {
    int count = 0, n = nums.size();

    for (std::size_t i = 0; i < n - 2; ++i) {
      if (0 == nums[i]) {
        nums[i] ^= 1;
        nums[i + 1] ^= 1;
        nums[i + 2] ^= 1;
        ++count;
      }
    }

    return (1 == nums[n - 2] && 1 == nums[n - 1]) ? count : -1;
  }
};

TEST(SolutionTest, Test1) {
  Solution solution;
  std::vector<int> nums{0, 1, 1, 1, 0, 0};
  EXPECT_EQ(3, solution.minOperations(nums));
}

TEST(SolutionTest, Test2) {
  Solution solution;
  std::vector<int> nums{0, 1, 1, 1};
  EXPECT_EQ(-1, solution.minOperations(nums));
}
