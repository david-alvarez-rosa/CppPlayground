#include <bits/stdc++.h>
using namespace std;

vector<string> ParseInputFile(const string& file_name) {
  vector<string> input;
  ifstream file_stream{file_name};
  string line;
  while (file_stream >> line) input.emplace_back(line);
  return input;
}

bool IsDigit(char c) { return c - '0' >= 0 && c - '0' <= 9; }

bool IsSymbol(char c) { return c != '.' && !IsDigit(c); }

bool IsAdjacentToSymbol(const vector<string>& input, int i, int j) {
  if (i - 1 >= 0 && IsSymbol(input[i - 1][j])) return true;
  if (i - 1 >= 0 && j - 1 >= 0 && IsSymbol(input[i - 1][j - 1])) return true;
  if (i - 1 >= 0 && j + 1 < input[0].size() && IsSymbol(input[i - 1][j + 1])) return true;
  if (j - 1 >= 0 && IsSymbol(input[i][j - 1])) return true;
  if (j + 1 < input[0].size() && IsSymbol(input[i][j + 1])) return true;
  if (i + 1 < input.size() && IsSymbol(input[i + 1][j])) return true;
  if (i + 1 < input.size() && j - 1 >= 0 && IsSymbol(input[i + 1][j - 1])) return true;
  if (i + 1 < input.size() && j + 1 < input[0].size() && IsSymbol(input[i + 1][j + 1])) return true;
  return false;
}

int Solve(const vector<string>& input) {
  int ans{0};
  for (int i{0}; i < input.size(); ++i) {
    int current{0};
    bool is_part_number{false};
    for (int j{0}; j < input[0].length(); ++j) {
      const auto c = input[i][j];
      if (IsDigit(c)) {
        current = 10 * current + c - '0';
        if (IsAdjacentToSymbol(input, i, j)) is_part_number = true;
      } else {
        if (is_part_number) ans += current;
        current = 0;
        is_part_number = false;
      }
    }
    if (is_part_number) ans += current;
  }
  return ans;
}

int main(int argc, char* argv[]) {
  auto input = ParseInputFile(argv[1]);
  cout << Solve(input) << endl;
}
