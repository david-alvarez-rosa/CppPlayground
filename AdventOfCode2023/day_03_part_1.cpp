#include <bits/stdc++.h>
using namespace std;

vector<string> engine;

void ParseInputFile(const string& file_name) {
  ifstream file_stream{file_name};
  string line;
  while (file_stream >> line) engine.emplace_back(line);
}

bool IsDigit(char c) { return c - '0' >= 0 && c - '0' <= 9; }

bool IsSymbol(char c) { return c != '.' && !IsDigit(c); }

bool IsValidPosition(pair<int, int> pos) {
  auto [i, j] = pos;
  return i >= 0 && i < engine.size() && j >= 0 && j < engine[0].size();
}

bool IsAdjacentToSymbol(int i, int j) {
  const vector<pair<int, int>> adjacent_positions = {
      {i - 1, j}, {i - 1, j - 1}, {i - 1, j + 1}, {i, j - 1},
      {i, j + 1}, {i + 1, j},     {i + 1, j - 1}, {i + 1, j + 1},
  };

  return any_of(
      adjacent_positions.cbegin(), adjacent_positions.cend(), [](auto pos) {
        return IsValidPosition(pos) && IsSymbol(engine[pos.first][pos.second]);
      });
}

int Solve() {
  int ans{0};
  for (int i{0}; i < engine.size(); ++i) {
    int current{0};
    bool is_part_number{false};
    for (int j{0}; j < engine[0].length(); ++j) {
      const auto c = engine[i][j];
      if (IsDigit(c)) {
        current = 10 * current + c - '0';
        if (IsAdjacentToSymbol(i, j)) is_part_number = true;
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
  ParseInputFile(argv[1]);
  cout << Solve() << endl;
}
