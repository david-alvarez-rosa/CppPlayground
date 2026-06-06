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

int Power(const Game& game) {
  int min_red{0}, min_green{0}, min_blue{0};
  for (auto reveal : game) {
    min_red = max(min_red, reveal["red"]);
    min_green = max(min_green, reveal["green"]);
    min_blue = max(min_blue, reveal["blue"]);
  }
  return min_red * min_green * min_blue;
}

int Solve(const vector<Game>& games) {
  return accumulate(
      games.cbegin(), games.cend(), 0,
      [](int total, const Game& game) { return total + Power(game); });
}

int main(int argc, char* argv[]) {
  auto input_games = ParseInputFile(argv[1]);
  cout << Solve(input_games) << endl;
}
