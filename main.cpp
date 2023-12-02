#include <bits/stdc++.h>
using namespace std;

vector<string> ParseInputFile(const string& file_name) {
  vector<string> input;
  ifstream file_stream{file_name};
  string line;
  while (file_stream >> line) input.emplace_back(line);
  return input;
}

int ParseDigit(const string& l, int i) {
  if (const auto c{l[i] - '0'}; c >= 0 && c <= 9) return c;
  if (l.substr(i, 3) == "one") return 1;
  if (l.substr(i, 3) == "two") return 2;
  if (l.substr(i, 5) == "three") return 3;
  if (l.substr(i, 4) == "four") return 4;
  if (l.substr(i, 4) == "five") return 5;
  if (l.substr(i, 3) == "six") return 6;
  if (l.substr(i, 5) == "seven") return 7;
  if (l.substr(i, 5) == "eight") return 8;
  if (l.substr(i, 4) == "nine") return 9;
  return -1;
}

int Solve(const vector<string>& input) {
  int ans{0};

  for (const auto& l : input) {
    int first{-1}, last{-1};
    for (int i{0}; i < l.length(); i++) {
      if (const auto d{ParseDigit(l, i)}; d != -1) {
        if (first == -1) first = d;
        last = d;
      }
    }
    ans += 10 * first + last;
  }

  return ans;
}

int main(int argc, char* argv[]) {
  auto input = ParseInputFile(argv[1]);
  cout << Solve(input) << endl;
}
