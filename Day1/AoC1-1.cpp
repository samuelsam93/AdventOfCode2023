#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

int get_cal_val(string input_line) {
  int first, last;
    bool first_flag = true;
    for (int i=0; i<input_line.length(); i++){
      if (isdigit(input_line[i]) && first_flag) {
        first = input_line[i] - 48;
        last = input_line[i] - 48;
        first_flag = false;
      } else if (isdigit(input_line[i])) {
        last = input_line[i] - 48;
      }
    }
  cout << input_line << " first digit: " << first << " last digit: " << last << " cal val is: " << (first*10) + last << "\n";
  return (first*10) + last;
}

int main() {
  ifstream input;
  input.open("AoC1.txt", ios::in);
  string in_string;
  int result = 0;
  while (getline(input, in_string)) {
    int cal_val = get_cal_val(in_string);    
    result += cal_val;
  }
  input.close();

  cout << "final result: " << result << endl;

  return 0;
}