#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

long int getVal(string* line) {
  line->erase(0, line->find(":")+1);
  while (line->find(" ") != string::npos) {
    line->erase(line->find(" "), 1);
  }
  long int result = stol(*line);
  return result;
}

// Brute force method will run, but will take a long time
// int calculateRecordHolds(int race_time, int record_dist) {
//   cout << "race length: " << race_time << "current record distance: " << record_dist << "\n\n";
//   vector<int> record_holds;
//   for (int i=0;i<race_time;i++) {
//     if (i*(race_time-i) > record_dist) {
//       cout << "hold time: " << i << " beats record with a distance of " << (long int)(i*(race_time-i)) << "\n";
//       record_holds.push_back(i);
//     }
//   }
//   return record_holds.size();
// }

// assumption: I think this makes sort of a bell curve, so if we find the first and last indices that create a new record,
// we can assume that all the values in between also create a new record
long int calculateRecordHolds(long int race_time, long int record_dist) {
  cout << "race length: " << race_time << " current record distance: " << record_dist << "\n\n";
  vector<int> record_holds;
  long int i=0;
  while ((i*(race_time-i)) < record_dist && i>=0) {
    i++;
    if (i%1000000 == 0) {
      cout << "checking for lowest: " << i << "\n";
    }
  }
  long int shortest_hold = i;
  cout << "\n\n shortest hold time found: " << shortest_hold << "\n\n";
  i = race_time;
  while ((long int)(i*(race_time-i)) < record_dist && i>0) {
    i--;
    if (i%1000000 == 0) {
      cout << "checking for highest: " << i << "\n";
    }
  }
  long int longest_hold = i;
  cout << "\n\n longest hold time found: " << longest_hold << "\n\n";

  // plus 1 so that it's inclusive
  return longest_hold-shortest_hold+1;
}

int main() {
  ifstream input;
  input.open("AoC6.txt", ios::in);
  string time_line;
  getline(input, time_line);
  string dist_line;
  getline(input, dist_line);
  long int result = 1;
  // cout << time_line;
  long int race_time = getVal(&time_line);
  long int record_dist = getVal(&dist_line);
  result = calculateRecordHolds(race_time, record_dist);

  cout << "final result: " << result;
}