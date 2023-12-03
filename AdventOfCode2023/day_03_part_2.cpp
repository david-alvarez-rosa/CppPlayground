#include <bits/stdc++.h>
using namespace std;

using Pos = pair<int, int>;

vector<string> engine;

void ParseInputFile(const string& file_name) {
  ifstream file_stream{file_name};
  string line;
  while (file_stream >> line) engine.emplace_back(line);
}

bool IsDigit(char c) { return c - '0' >= 0 && c - '0' <= 9; }

bool IsValidPosition(Pos pos) {
  auto [i, j] = pos;
  return i >= 0 && i < engine.size() && j >= 0 && j < engine[0].size();
}

set<Pos> GetAdjacentAsterisks(int i, int j) {
  const vector<Pos> adjacent_positions = {
      {i - 1, j}, {i - 1, j - 1}, {i - 1, j + 1}, {i, j - 1},
      {i, j + 1}, {i + 1, j},     {i + 1, j - 1}, {i + 1, j + 1},
  };

  set<Pos> adjacent_asterisks;
  for (auto pos : adjacent_positions)
    if (IsValidPosition(pos) && engine[pos.first][pos.second] == '*')
      adjacent_asterisks.insert(pos);

  return adjacent_asterisks;
}

int Solve() {
  int ans{0};
  map<Pos, vector<int>> m;
  for (int i{0}; i < engine.size(); ++i) {
    int current{0};
    set<Pos> adjacent_asterisks;
    for (int j{0}; j < engine[0].length(); ++j) {
      const auto c = engine[i][j];
      if (IsDigit(c)) {
        current = 10 * current + c - '0';
        auto current_adjacent_asterisks = GetAdjacentAsterisks(i, j);
        adjacent_asterisks.insert(current_adjacent_asterisks.begin(),
                                  current_adjacent_asterisks.end());
      } else {
        for (const auto asterisk : adjacent_asterisks)
          m[asterisk].push_back(current);
        current = 0;
        adjacent_asterisks = {};
      }
    }
    for (const auto asterisk : adjacent_asterisks)
      m[asterisk].emplace_back(current);
  }

  for (const auto& [asterisk, numbers] : m)
    if (numbers.size() == 2) ans += numbers[0] * numbers[1];

  return ans;
}

int main(int argc, char* argv[]) {
  ParseInputFile(argv[1]);
  cout << Solve() << endl;
}
