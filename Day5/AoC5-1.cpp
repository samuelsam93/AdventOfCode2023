#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

vector<long long int> getSeeds(string* line) {
  line->erase(0, line->find(":")+2);
  vector<long long int> seeds;
  while (!(*line).empty()) {
    if ((*line)[0] == ' ') {
      line->erase(0, 1);
    }
    long long int curr_num = stoll(line->substr(0, min(line->find(" "), line->length())));
    seeds.push_back(curr_num);
    if (line->find(" ") != string::npos) {
      line->erase(0, line->find(" ")+1);
    } else {
      line->erase(0, line->length());
    }

  }
  return seeds; 
}

void checkMapLine(vector<long long int>* curr_vals, vector<long long int>* new_vals, long long int src_start, long long int dest_start, long long int len) {
  for (int i=0; i<curr_vals->size(); i++) {
    if ((*curr_vals)[i] >= src_start && (*curr_vals)[i]<src_start+len) {
      cout << "curr val: " << (*curr_vals)[i] << " being caught within this map\n";
      new_vals->push_back(dest_start + ((*curr_vals)[i]-src_start));
      curr_vals->erase(curr_vals->begin()+i); 
      i--;
    }
  }
}

vector<long long int> processMap(ifstream* input, vector<long long int>* curr_vals) {
  cout << "curr_vals: ";
  for (int i=0; i<curr_vals->size();i++) {
    cout << (*curr_vals)[i] << " ";
  }
  cout << "\n";
  string map_line;
  getline(*input, map_line);
  vector<long long int> new_vals;
  while (!map_line.empty()) {
    cout << map_line << "\n";
    // cout << "{" << map_line.substr(0, map_line.find(" ")) << "}\n";
    long long int dest_start = stoll(map_line.substr(0, map_line.find(" ")));
    map_line.erase(0, map_line.find(" ")+1);
    // cout << "{" << map_line.substr(0, map_line.find(" ")) << "}\n";
    long long int src_start = stoll(map_line.substr(0, map_line.find(" ")));
    map_line.erase(0, map_line.find(" ")+1);
    // cout << "{" << map_line.substr(0, map_line.size()) << "}\n";
    long long int len = stoll(map_line.substr(0, map_line.size()));
    
    cout << "dest: " << dest_start << " source: " << src_start << " length: " << len << "\n";
    checkMapLine(curr_vals, &new_vals, src_start, dest_start, len);

    if (!getline(*input, map_line)){
      break;
    }
  }
  for (int i=0; i<curr_vals->size(); i++) {
    new_vals.push_back((*curr_vals)[i]);
  }
  return new_vals;
}

int main() {
  ifstream input;
  input.open("AoC5.txt", ios::in);
  string seed_line;
  getline(input, seed_line);
  // int result = 0;
  vector<long long int> curr_vals = getSeeds(&seed_line);
  cout << "curr_vals: ";
  for (int i=0; i<curr_vals.size();i++) {
    cout << curr_vals[i] << " ";
  }
  cout << "\n";
  string empty_line;
  getline(input, empty_line);
  string map_name;
  while (getline(input, map_name)) {
    vector<long long int> new_vals = processMap(&input, &curr_vals);
    curr_vals = new_vals;
  }

  input.close();

  cout << "final values: {";
  for (int i=0; i<curr_vals.size();i++) {
    cout << curr_vals[i] << " ";
  }
  cout << "}\n";

  long long int result = *min_element(curr_vals.begin(), curr_vals.end());

  cout << "final result: " << result << endl;

  return 0;
}