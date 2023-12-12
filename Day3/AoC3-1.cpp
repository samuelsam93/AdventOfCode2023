#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

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


/**
 * @brief checks if the number at a given location has an adjascent symbol (other than '.')
 * 
 * @param row - the row containing our number
 * @param index - the starting index of our number
 * @param num_len - the length of our number
 * @param above - the row above the row containing our number from the input
 * @param below - the row below the row containing our number from the input
 * @return bool - whether or not there is a symbol adjascent to our number
 */
bool isSymbolAdjascent(string row, int index, int num_len, string above, string below) {
  bool symbol_adjascent = false;

  // pointers for the grid location immediately before and after the number we're checking.
  // ternary to make sure pointers stay in range
  int l = (index > 0) ? index-1 : index;
  int r = (index + num_len < row.length()) ? index + num_len : index + num_len-1;

  // check in line with number. if either isn't '.', return true
  if ((row[l] != '.' && l>0) || (row[r] != '.' && r<row.length()-1)) {
    return true;
  }

  // check above and below number (including diagonal due to l and r) for any symbols
  for (int i=0; i<r+1-l; i++) {
    if (!above.empty()) {
      if (above[l+i] != '.') {
        symbol_adjascent = true;
        break;
      }
    }
    if (!below.empty()) {
      if (below[l+i] != '.') {
        symbol_adjascent = true;
        break;
      }
    }
  }

  return symbol_adjascent;
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
    if (isdigit(row[i])) {
      num_len = getNumLength(row, i);
      // check if there is a symbol adjascent to detected number, if so, add it to running count
      bool symbol_adjascent = isSymbolAdjascent(row, i, num_len, above, below);
      if (symbol_adjascent) {
        cout << "number added to count: " << row.substr(i, num_len);
        row_result += stoi(row.substr(i, num_len));
        cout << " running count: " << row_result << "\n"; 
      }
      // if number was detected, skip ahead to next character that is not part of the current number
      i+=num_len-1;
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