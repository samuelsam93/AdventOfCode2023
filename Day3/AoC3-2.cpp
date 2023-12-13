#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;
/**
 * @brief Get the length (in number of digits) of the number in the given line starting at the given index
 * 
 * @param line - the line of the input that holds the desired number
 * @param index - the index within the line of the first digit of the desired number 
 * @return - the number of digits as an integer
 */
int getNumLength(string line, int index) {
  int num_length = 1;
  while (isdigit(line[index+1])){
    num_length++;
    index++;
  }
  return num_length;
}

int getNumber(string row, int index) {
  bool front_found = false; bool back_found = false;
  string number = row.substr(index, 1);
  int i = 1;
  while (!(front_found && back_found)) {
    if (!front_found){
      if (isdigit(row[index-i])) {
        number = row[index-i] + number;
      } else {
        front_found = true;
      }
    }
    if (!back_found) {
      if (isdigit(row[index+i])) {
        number = number + row[index+i];
      } else {
        back_found = true;
      }
    }
    i++;
  }
  cout << number << "\n";
  return stoi(number);
}

int multiplyAdjascentNums(string row, int index, string above, string below) {
  // check in line with number. if either isn't '.', return true
  vector<int> adj_numbers;
  if (index>0) {
    if (row[index-1] != '.') {
      adj_numbers.push_back(getNumber(row, index-1));
    }
  }
  if (index < row.length()-1) {
    if (row[index+1] != '.') {
      adj_numbers.push_back(getNumber(row, index+1));
    }
  }

  // check above and below number (including diagonal due to l and r) for any symbols
  for (int i=-1; i<2; i++) {
    if (!above.empty() && (index+i>=0) && (index+1 < above.length()-1)) {
      if (above[index+i] != '.') {
        if (i<0) {
          adj_numbers.push_back(getNumber(above, index+i));
        }
        if (i>=0 && above[index+i-1] == '.') {
          adj_numbers.push_back(getNumber(above, index+i));
        }
      }
    }
    if (!below.empty() && (index+i>=0) && (index+1 < below.length()-1)) {
      if (below[index+i] != '.') {
        // cout << "below[index+i-1]" << below[index+i-1]<< "\n";
        if (i<0) {
          adj_numbers.push_back(getNumber(below, index+i));
        }
        if (i>=0 && below[index+i-1] == '.') {
          adj_numbers.push_back(getNumber(below, index+i));
        }
      }
    }
  }

  // for (int i=0; i<adj_numbers.size(); i++) {
  //   cout << "adj numbers[i]: " << adj_numbers[i] << "\n";
  // }
  if (adj_numbers.size() == 2) {
    return adj_numbers[0]*adj_numbers[1];
  } else {
    return 0;
  }
}

/**
 * @brief - loop through a row of input given the rows above and below it to search for numbers with adjascent symbols
 * 
 * @param row - row of input currently being searched
 * @param above - row of input above the row being searched
 * @param below - row of input below the row being searched
 * @return int 
 */
int searchRow(string row, string above, string below) {
  int row_result = 0;
  // loop through all the elements in the row
  for (int i=0; i<row.length(); i++) {
    int num_len;
    // if digit is detected, determine how long the number is
    if (row[i] == '*') {
      // check if there is a symbol adjascent to detected number, if so, add it to running count
      int adjascent_nums_prod = multiplyAdjascentNums(row, i, above, below);
      // cout << "number added to count: " << row.substr(i, num_len);
      row_result += adjascent_nums_prod;
    }
  }
  cout << "row total: " << row_result << "\n";
  return row_result;
}

int main() {
  ifstream input;
  input.open("AoC3.txt", ios::in);
  string bottom = ""; string middle = ""; string top ="";
  int result = 0;
  // loop through each line of input
  while (getline(input, bottom)) {
    result += searchRow(middle, top, bottom);
    // shift each row being checked up by one
    top = middle;
    middle = bottom;
    cout << "running total: " << result << "\n";
  }
  result += searchRow(middle, top, "");

  input.close();
  cout << "final result: " << result << endl;

  return 0;
}