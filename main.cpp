#include <iostream>
#include <string>

using namespace std;

class Solution {
 public:
  string mergeAlternately(string word1, string word2) {
    int n1 = word1.length();
    int n2 = word2.length();
    int n = min(n1, n2);
    string ans;

    for (int i = 0; i < n; ++i) {
      ans = ans + word1[i] + word2[i];
    }

    for (int i = n; i < n1; ++i) {
      ans = ans + word1[i];
    }

    for (int i = n; i < n2; ++i) {
      ans = ans + word2[i];
    }

    return ans;
  }
};

int main() {
  Solution solution;
  cout << solution.mergeAlternately("abc", "pqr") << endl;
  string s;
}
