#include <bits/stdc++.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace std;
using namespace testing;

class Solution {
 public:
  vector<string> uncommonFromSentences(string s1, string s2) {
    auto words1{extractWords(s1)};
    auto words2{extractWords(s2)};

    unordered_map<string, int> fqs;
    for (const auto& word1 : words1) fqs[word1]++;
    for (const auto& word2 : words2) fqs[word2]++;

    vector<string> ans;
    for (const auto [word, fq] : fqs)
      if (fq == 1) ans.push_back(word);

    return ans;
  }

 private:
  vector<string> extractWords(const string& s) {
    vector<string> words;

    for (size_t i{0}, prev{0}; i <= s.length(); ++i) {
      if (s[i] == ' ' || i == s.length()) {
        words.push_back(s.substr(prev, i - prev));
        prev = i + 1;
      }
    }

    return words;
  }
};

TEST(SolutionTest, Test1) {
  Solution solution;
  string s1{"this apple is sweet"};
  string s2{"this apple is sour"};
  EXPECT_THAT(solution.uncommonFromSentences(s1, s2),
              UnorderedElementsAre("sweet", "sour"));
}

TEST(SolutionTest, Test2) {
  Solution solution;
  string s1{"apple apple"};
  string s2{"banana"};
  EXPECT_THAT(solution.uncommonFromSentences(s1, s2),
              UnorderedElementsAre("banana"));
}
