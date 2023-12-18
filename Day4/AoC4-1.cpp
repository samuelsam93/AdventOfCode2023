#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

int getCardNumber(string* line) {
  int card_num = stoi(line->substr(5, line->find(":")));
  line->erase(0, line->find(":")+2);
  return card_num; 
}

vector<int> processWinningNumbers(string* card) {
  vector<int> winners;
  if ((*card)[0] == ' ') {
    card->erase(0, 1);
  }
  while (card->substr(0, 1) != "|") {
    winners.push_back(stoi(card->substr(0, card->find(" "))));
    card->erase(0, card->find(" ")+1);

    if ((*card)[0] == ' ') {
      card->erase(0, 1);
    }
  }
  card->erase(0, 2);
  return winners;
}

int processPlayerNumbers(string* card, vector<int> winners) {
  vector<int> players;
  int result = 0;
  cout << "found: ";
  while (!card->empty()) {
    if ((*card)[0] == ' ') {
      card->erase(0, 1);
    }

    int curr_num = stoi(card->substr(0, min(card->find(" "), card->length())));
    if (find(winners.begin(), winners.end(), curr_num) != winners.end()) {
      cout << curr_num << " ";
      if (result) {
        result*=2;
      } else {
        result+=1;
      }
    }
    if (card->find(" ") != string::npos) {
      card->erase(0, card->find(" ")+1);
    } else {
      card->erase(0, card->length());
    }
  }
  cout << "\n";
  return result;
}

int main() {
  ifstream input;
  input.open("AoC4.txt", ios::in);
  string card;
  int result = 0;
  while (getline(input, card)) {
    int card_number = getCardNumber(&card);
    cout << "card no: " << card_number << "\n";
    cout << "card: " << card << "\n";
    vector<int> winners = processWinningNumbers(&card);
    int card_result = processPlayerNumbers(&card, winners);
    cout << "card result: " << card_result << "\n";

    result += card_result;
  }
  input.close();

  cout << "final result: " << result << endl;

  return 0;
}