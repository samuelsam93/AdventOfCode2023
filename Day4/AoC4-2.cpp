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
  // cout << *card << "\n";
  if ((*card)[0] == ' ') {
    card->erase(0, 1);
  }
  // cout << *card << "\n";
  while (card->substr(0, 1) != "|") {
    // cout << card->substr(0, card->find(" "));
    winners.push_back(stoi(card->substr(0, card->find(" "))));
    card->erase(0, card->find(" ")+1);

    if ((*card)[0] == ' ') {
      card->erase(0, 1);
    }
  }
  card->erase(0, 2);
  return winners;
}

// string processWinningNumbers(string* card) {
//   string winners = card->substr(0, card->find("|"));
//   card->erase(0, card->find("|")+2);
//   return winners;
// }

int processPlayerNumbers(string* card, vector<int> winners) {
  vector<int> players;
  int result = 0;
  cout << "found: ";
  while (!card->empty()) {
    // cout << "card from player numbers: " << *card << "\n";
    if ((*card)[0] == ' ') {
      card->erase(0, 1);
    }
    // cout << "card from player numbers 2: " << *card << "\n";

    int curr_num = stoi(card->substr(0, min(card->find(" "), card->length())));
    // check if curr num is in winners
    if (find(winners.begin(), winners.end(), curr_num) != winners.end()) {
      cout << curr_num << " ";
      result+=1;
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

void updateCardAmts(vector<int>* card_amts, int curr_card, int cards_result) {
  if (curr_card > card_amts->size()-1) {
    cout << "adding card number: " << curr_card << "\n";
    card_amts->push_back(1);
  }
  for (int i=1; i<cards_result+1; i++) {
    if (curr_card+i > card_amts->size()-1) {
      cout << "adding card number: " << curr_card+i << "\n";
      card_amts->push_back(1);
    }
    (*card_amts)[curr_card+i] += (*card_amts)[curr_card];
  }
}

int main() {
  cout<< __cplusplus << "\n";
  ifstream input;
  input.open("AoC4.txt", ios::in);
  string card;
  vector<int> card_amts;
  card_amts.push_back(0);
  card_amts.push_back(1);
  int result = 0;
  while (getline(input, card)) {
    int curr_card = getCardNumber(&card);
    cout << "card no: " << curr_card << "\n";
    cout << "card: " << card << "\n";
    vector<int> winners = processWinningNumbers(&card);
    int card_result = processPlayerNumbers(&card, winners);
    updateCardAmts(&card_amts, curr_card, card_result);
  }
  
  cout << "size of card_amts: " << card_amts.size() << "\n";
  for (int i=0;i<card_amts.size();i++) {
    cout << card_amts[i] << " ";
    result+=card_amts[i];
  }

  cout << "\n";

  input.close();

  cout << "final result: " << result << endl;

  return 0;
}