#include <vector>
#include <unordered_map>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

class Solution {
 public:
  std::vector<int> twoSum(std::vector<int>& nums, int target) {
    std::unordered_map<int, int> mp;  // (nums[i], i)
    for (int i{0}; i < nums.size(); i++) {
      const auto complement = target - nums[i];
      if (mp.contains(complement)) {
        return {i, mp[complement]};
      }
      mp[nums[i]] = i;
    }
    return {0, 0};
  }
};

TEST(SolutionTest, Test1) {
  Solution solution;
  std::vector<int> nums{2, 7, 11, 15};
  EXPECT_THAT(solution.twoSum(nums, 9),
              testing::UnorderedElementsAreArray(0, 1));
}

TEST(SolutionTest, Test2) {
  Solution solution;
  std::vector<int> nums{3, 2, 4};
  EXPECT_THAT(solution.twoSum(nums, 6),
              testing::UnorderedElementsAreArray(1, 2));
}

TEST(SolutionTest, Test3) {
  Solution solution;
  std::vector<int> nums{3, 3};
  EXPECT_THAT(solution.twoSum(nums, 6),
              testing::UnorderedElementsAreArray(0, 1));
}
