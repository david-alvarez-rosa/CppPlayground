#include <bits/stdc++.h>
#include <gtest/gtest.h>

using namespace std;

class Solution {
 public:
  string encode(vector<string>& strs) {
    string encoded;
    for (const auto& str : strs) encoded += to_string(str.length()) + '#' + str;
    return encoded;
  }

  vector<string> decode(string s) {
    vector<string> decoded;
    auto i{0};
    while (i < s.length()) {
      string curr_s;
      auto length{0};
      while (s[i] != '#') {
        length *= 10;
        length += (s[i] - '0');
        i++;
      }
      i++;
      while (length--) {
        curr_s += s[i];
        i++;
      }
      decoded.push_back(curr_s);
    }

    return decoded;
  }
};

TEST(SolutionTest, Test1) {
  Solution solution;
  vector<string> strs{"neet", "code", "love", "you"};
  EXPECT_EQ(strs, solution.decode(solution.encode(strs)));
}

TEST(SolutionTest, Test2) {
  Solution solution;
  vector<string> strs{"we", "say", ":", "yes"};
  EXPECT_EQ(strs, solution.decode(solution.encode(strs)));
}
