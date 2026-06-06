#include <bits/stdc++.h>
#include <gtest/gtest.h>

using namespace std;

class Solution {
 public:
  int bagOfTokensScore(vector<int>& tokens, int power) {
    sort(tokens.begin(), tokens.end());
    unsigned int max_score{0}, score{0};
    if (tokens.size() == 0) return 0;
    size_t i{0}, j{tokens.size() - 1};
    while (i <= j) {
      if (power >= tokens[i]) {
        power -= tokens[i];
        score++;
        i++;
      } else if (score >= 1) {
        power += tokens[j];
        score--;
        j--;
      } else {
        break;
      }
      max_score = max(max_score, score);
    }
    return max_score;
  }
};

TEST(SolutionTest, Test1) {
  Solution solution;
  vector<int> tokens{100};
  EXPECT_EQ(0, solution.bagOfTokensScore(tokens, 50));
}

TEST(SolutionTest, Test2) {
  Solution solution;
  vector<int> tokens{200, 100};
  EXPECT_EQ(1, solution.bagOfTokensScore(tokens, 150));
}

TEST(SolutionTest, Test3) {
  Solution solution;
  vector<int> tokens{100, 200, 300, 400};
  EXPECT_EQ(2, solution.bagOfTokensScore(tokens, 200));
}
