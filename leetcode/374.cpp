#include <bits/stdc++.h>
#include <gtest/gtest.h>

using namespace std;

class Solution {
 public:
  explicit Solution(int pick) : pick_{pick} {}

  int guessNumber(int n) { return guessNumber(1, n); }

  int guessNumber(int low, int high) {
    const int mid = ((long)high + (long)low) / 2;
    if (guess(mid) == -1) return guessNumber(low, mid - 1);
    if (guess(mid) == 1) return guessNumber(mid + 1, high);
    return mid;
  }

 private:
  int guess(int num) {
    if (num > pick_) return -1;
    if (num < pick_) return 1;
    return 0;
  }

  int pick_;
};

TEST(SolutionTest, Test1) {
  constexpr int pick{6};
  Solution solution(pick);
  EXPECT_EQ(pick, solution.guessNumber(10));
}

TEST(SolutionTest, Test2) {
  constexpr int pick{1};
  Solution solution(pick);
  EXPECT_EQ(pick, solution.guessNumber(1));
}

TEST(SolutionTest, Test3) {
  constexpr int pick{1};
  Solution solution(pick);
  EXPECT_EQ(pick, solution.guessNumber(2));
}
