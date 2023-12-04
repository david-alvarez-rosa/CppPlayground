#include <bits/stdc++.h>
using namespace std;

struct Scratchcard {
  vector<int> winning_numbers;
  vector<int> numbers;
  int quantity{1};
  int unprocessed_quantity{1};
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
  auto clean_line =
      line.substr(semicolon_pos + 1, line.size() - semicolon_pos - 1);
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

int GetNumberMatches(const Scratchcard& scratchcard) {
  int number_matches{0};
  for (const auto number : scratchcard.numbers) {
    if (find(scratchcard.winning_numbers.cbegin(),
             scratchcard.winning_numbers.end(),
             number) != scratchcard.winning_numbers.cend()) {
      ++number_matches;
    }
  }
  return number_matches;
}

int Solve(vector<Scratchcard>& scratchcards) {
  int won_scratchcards{0};
  int current_won_scratchcards = scratchcards.size();
  while (current_won_scratchcards != won_scratchcards) {
    won_scratchcards = current_won_scratchcards;
    for (int i = 0; i < scratchcards.size(); ++i) {
      auto& scratchcard = scratchcards[i];
      auto number_matches = GetNumberMatches(scratchcard);
      while (number_matches--) {
        current_won_scratchcards += scratchcard.unprocessed_quantity;
        scratchcards[i + number_matches + 1].quantity +=
            scratchcard.unprocessed_quantity;
        scratchcards[i + number_matches + 1].unprocessed_quantity +=
            scratchcard.unprocessed_quantity;
      }
      scratchcard.unprocessed_quantity = 0;
    }
  }

  return won_scratchcards;
}

int main(int argc, char* argv[]) {
  auto input_scratchcards = ParseInputFile(argv[1]);
  cout << Solve(input_scratchcards) << endl;
}
