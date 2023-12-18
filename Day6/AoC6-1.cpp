#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

int getNextVal(string* line) {
  while (!isdigit((*line)[0])) {
    line->erase(0,1);
  }
  int result = stoi(line->substr(0, line->find(" ")));
  line->erase(0, line->find(" "));
  return result;
}

int calculateRecordHolds(int race_time, int record_dist) {
  cout << "race length: " << race_time << "current record distance: " << record_dist << "\n\n";
  vector<int> record_holds;
  for (int i=0;i<race_time;i++) {
    if (i*(race_time-i) > record_dist) {
      cout << "hold time: " << i << " beats record with a distance of " << i*(race_time-i) << "\n";
      record_holds.push_back(i);
    }
  }
  return record_holds.size();
}

int main() {
  ifstream input;
  input.open("AoC6.txt", ios::in);
  string time_line;
  getline(input, time_line);
  string dist_line;
  getline(input, dist_line);
  int result = 1;
  // cout << time_line;
  while (time_line.length()) {
    int race_time = getNextVal(&time_line);
    int record_dist = getNextVal(&dist_line);
    // cout << "race_time " << race_time << " record_dist " << record_dist << "\n";
    result *= calculateRecordHolds(race_time, record_dist);
  }
  cout << "final result: " << result;
}