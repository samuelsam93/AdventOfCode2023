#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

int isTextNumber(string input_line, int loc) {
  if (isdigit(input_line[loc])) {
    return input_line[loc]-48;
  } 
  if (loc >= 2) {
    string last_three = input_line.substr(loc-2, 3);
    if (last_three == "one") {
      return 1;
    } else if (last_three == "two") {
      return 2;
    } else if (last_three == "six") {
      return 6;
    }
  }
  if (loc >= 3) {
    string last_four = input_line.substr(loc-3, 4);
    if (last_four == "four") {
      return 4;
    } else if (last_four == "five") {
      return 5;
    } else if (last_four == "nine") {
      return 9;
    } else if (last_four == "zero") {
      return 0;
    }
  }
  if (loc >= 4) {
    string last_five = input_line.substr(loc-4, 5);
    if (last_five == "three") {
      return 3;
    } else if  (last_five == "seven") {
      return 7;
    } else if (last_five == "eight") {
      return 8;
    }
  }
  return -1;
}

int get_cal_val(string input_line) {
  int first, last;
    bool first_flag = true;
    for (int i=0; i<input_line.length(); i++){
      int check_val = isTextNumber(input_line, i);
      if ((check_val >= 0) && first_flag) {
        first = check_val;
        last = check_val;
        first_flag = false;
      } else if (check_val >= 0) {
        last = check_val;
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