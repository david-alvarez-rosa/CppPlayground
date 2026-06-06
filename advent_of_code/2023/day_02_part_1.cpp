#include <bits/stdc++.h>
using namespace std;

using Reveal = unordered_map<string, int>;
using Game = vector<Reveal>;

vector<string> SplitByDelimiter(const string& s, char delimiter) {
  vector<string> splitted_string;
  string current;
  for (auto c : s) {
    if (c == delimiter) {
      splitted_string.emplace_back(current);
      current = "";
    } else {
      current += c;
    }
  }
  splitted_string.emplace_back(current);
  return splitted_string;
}

Reveal ParseRevealStr(const string& reveal_str) {
  Reveal reveal;
  for (const auto& color_reveal : SplitByDelimiter(reveal_str, ',')) {
    istringstream iss{color_reveal};
    int x;
    string color;
    iss >> x >> color;
    reveal[color] = x;
  }
  return reveal;
}

vector<Game> ParseInputFile(const string& file_name) {
  vector<Game> games;
  ifstream file_stream{file_name};
  string line;
  while (getline(file_stream, line)) {
    const auto semicolon_pos = line.find(":");
    const auto clean_line =
        line.substr(semicolon_pos + 1, line.size() - semicolon_pos - 1);
    Game game;
    for (const auto& reveal_str : SplitByDelimiter(clean_line, ';'))
      game.emplace_back(ParseRevealStr(reveal_str));
    games.emplace_back(game);
  }
  return games;
}

bool IsGamePossible(const Game& game) {
  return all_of(game.cbegin(), game.cend(), [](Reveal r) {
    return r["red"] <= 12 && r["green"] <= 13 && r["blue"] <= 14;
  });
}

int Solve(const vector<Game>& games) {
  int ans{0};
  for (int i{0}; i < games.size(); i++)
    if (IsGamePossible(games[i])) ans += i + 1;

  return ans;
}

int main(int argc, char* argv[]) {
  auto input_games = ParseInputFile(argv[1]);
  cout << Solve(input_games) << endl;
}
