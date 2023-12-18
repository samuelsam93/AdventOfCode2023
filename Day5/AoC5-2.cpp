#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

class range {
  public:
    long long int high;
    long long int low;
    range() {}
    range(long long int low_, long long int high_) {
      high = high_;
      low = low_;
    }

    bool isOverlapping(range other_range) {
      if (low <= other_range.high && other_range.low <= high) {
        return true;
      }
      return false;
    }

    range getIntersection(range other_range) {
      return range(max(low, other_range.low), min(high, other_range.high));
    }
};

vector<range> getSeeds(string* line) {
  cout << "inside get seeds... ";
  line->erase(0, line->find(":")+2);
  vector<range> seeds;
  while (!(*line).empty()) {
    if ((*line)[0] == ' ') {
      line->erase(0, 1);
    }
    range seed_range;
    seed_range.low = stoll(line->substr(0, min(line->find(" "), line->length())));

    line->erase(0, line->find(" ")+1);

    seed_range.high = seed_range.low + stoll(line->substr(0, min(line->find(" "), line->length())))-1;
    seeds.push_back(seed_range);
    if (line->find(" ") != string::npos) {
      line->erase(0, line->find(" ")+1);
    } else {
      line->erase(0, line->length());
    }
    // cout << "range start: " << range_start << "\n";
    // for (int i=0;i<range_len;i++) {
    //   seeds.push_back(range_start+i);
    // }
  }
  cout << "seeds acquired \n";
  return seeds; 
}

void checkMapLine(vector<range>* curr_vals, vector<range>* new_vals, range dest_range, range src_range) {
  for (int i=0; i<curr_vals->size(); i++) {

    if ((*curr_vals)[i].isOverlapping(src_range)) {
      // cout << "curr val: " << (*curr_vals)[i].low << ", " << (*curr_vals)[i].high << " being caught within this map\n";
      range intersection = (*curr_vals)[i].getIntersection(src_range);


      long long int dest_low = max(dest_range.low, dest_range.low+(intersection.low-src_range.low));
      // cout << "dest_low " << dest_low << "\n";
      // cout << "dest_hig " << min(dest_low+(intersection.high-intersection.low), dest_range.high) << "\n";
      range intersection_dest(dest_low, min(dest_low+(intersection.high-intersection.low), dest_range.high));
      new_vals->push_back(intersection_dest);
      
      if ((*curr_vals)[i].low < src_range.low) {
        // cout << " in low\n";
        range new_range((*curr_vals)[i].low, src_range.low-1);
        curr_vals->push_back(new_range);
      }
      if ((*curr_vals)[i].high > src_range.high) {
        // cout << " in high\n";
        range new_range(src_range.high+1, (*curr_vals)[i].high);
        curr_vals->push_back(new_range);
      }
      curr_vals->erase(curr_vals->begin()+i); 
      
      i--;
    }
  }
}

vector<range> processMap(ifstream* input, vector<range>* curr_vals) {
  // cout << "curr_vals: ";
  // for (int i=0; i<curr_vals->size();i++) {
  //   cout << (*curr_vals)[i] << " ";
  // }
  cout << "\n";
  string map_line;
  getline(*input, map_line);
  vector<range> new_vals;
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
    
    range dest_range(dest_start, dest_start+len-1);
    range src_range(src_start, src_start+len-1);

    // cout << "dest: " << dest_start << " source: " << src_start << " length: " << len << "\n";
    checkMapLine(curr_vals, &new_vals, dest_range, src_range);

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
  long long int maxval = LLONG_MAX;
  ifstream input;
  input.open("AoC5.txt", ios::in);
  string seed_line;
  getline(input, seed_line);
  // int result = 0;
  vector<range> curr_vals = getSeeds(&seed_line);
  // cout << "curr_vals: ";
  // for (int i=0; i<curr_vals.size();i++) {
  //   cout << curr_vals[i] << " ";
  // }
  // cout << "\n";
  string empty_line;
  getline(input, empty_line);
  string map_name;
  while (getline(input, map_name)) {
    vector<range> new_vals = processMap(&input, &curr_vals);
    curr_vals = new_vals;

    // cout << "curr values: {";
    // for (int i=0; i<curr_vals.size();i++) {
    //   cout << "low: " << curr_vals[i].low << " high: " << curr_vals[i].high << " ";
    // }
    // cout << "}\n";
  }

  input.close();

  // cout << "final values: {";
  // for (int i=0; i<curr_vals.size();i++) {
  //   cout << "low: " << curr_vals[i].low << " high: " << curr_vals[i].high;
  // }
  // cout << "}\n";

  vector<long long int> lows;
  for(int i=0; i<curr_vals.size();i++) {
    lows.push_back(curr_vals[i].low);
  }
  long long int result = *min_element(lows.begin(), lows.end());

  cout << "final result: " << result << endl;

  return 0;
}