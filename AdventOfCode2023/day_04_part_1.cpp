#include <bits/stdc++.h>
using namespace std;

struct Scratchcard {
  vector<int> winning_numbers;
  vector<int> numbers;
};

vector<string> SplitByDelimiter(const string& s, char d) {
  vector<string> splitted_string;
  string current;
  for (const auto c : s) {
    if (c == d) {
      splitted_string.emplace_back(current);
      current = "";
    } else {
      current += c;
    }
  }
  splitted_string.emplace_back(current);
  return splitted_string;
}

Scratchcard ParseLine(const string& line) {
  auto semicolon_pos = line.find(":");
  auto clean_line = line.substr(semicolon_pos + 1, line.size() - semicolon_pos - 1);
  auto split_line = SplitByDelimiter(clean_line, '|');

  vector<int> winning_numbers;
  {
    istringstream iss{split_line[0]};
    int x;
    while (iss >> x) winning_numbers.emplace_back(x);
  }

  vector<int> numbers;
  {
    istringstream iss{split_line[1]};
    int x;
    while (iss >> x) numbers.emplace_back(x);
  }

  return {winning_numbers, numbers};
}

vector<Scratchcard> ParseInputFile(const string& file_name) {
  vector<Scratchcard> scratchcards;
  ifstream file_stream{file_name};
  string line;
  while (getline(file_stream, line)) scratchcards.emplace_back(ParseLine(line));
  return scratchcards;
}

int GetPoints(const Scratchcard& scratchcard) {
  int points{0};
  for (const auto number : scratchcard.numbers) {
    if (find(scratchcard.winning_numbers.cbegin(),
             scratchcard.winning_numbers.end(),
             number) != scratchcard.winning_numbers.cend()) {
      if (points)
        points *= 2;
      else
        points = 1;
    }
  }
  return points;
}

int Solve(const vector<Scratchcard>& scratchcards) {
  return accumulate(scratchcards.cbegin(), scratchcards.cend(), 0,
                    [](int total, const Scratchcard& scratchcard) {
                      return total + GetPoints(scratchcard);
                    });
}

int main(int argc, char* argv[]) {
  auto input_scratchcards = ParseInputFile(argv[1]);
  cout << Solve(input_scratchcards) << endl;
}
