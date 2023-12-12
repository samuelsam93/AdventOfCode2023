#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

int getGameNumber(string* line) {
  int game_num = stoi(line->substr(5, line->find(":")));
  line->erase(0, line->find(":")+2);
  return game_num; 
}

int getNumCubes(string* pull) {
  int num_cubes = stoi(pull->substr(0, pull->find(" ")));
  pull->erase(0, pull->find(" ")+1);
  return num_cubes;
}

string getColor(string* pull) {
  string color = pull->substr(0, min(pull->find(","), pull->length()));
  if (pull->find(",") != string::npos) {
    pull->erase(0, pull->find(",")+2);
  } else {
    pull->erase(0, pull->length());
  }

  return color;
}

bool processPull(string* game) {
  string pull;
  if (game->find(";") != string::npos){
    pull = game->substr(0, game->find(";"));
    game->erase(0, pull.length()+2);
  } else {
    pull = *game;
    game->erase(0, pull.length());
  }
  while (pull.length() > 0) {
    int num_cubes = getNumCubes(&pull);
    string color = getColor(&pull);
    if ((color == "red" && num_cubes > 12) || (color == "green" && num_cubes > 13) || (color == "blue" && num_cubes > 14)) {
      cout << "impossible game" << "\n";
      return false;
    }
  }
  
  return true;
}

int main() {
  ifstream input;
  input.open("AoC2.txt", ios::in);
  string game;
  int result = 0;
  while (getline(input, game)) {
    int game_num = getGameNumber(&game);
    cout << game_num << "\n";
    cout << game << "\n";
    bool game_result = true;
    while ((game.length() > 0) && (game_result)) {
      game_result = processPull(&game);
    }
    if (game_result) {
      result += game_num;
    }
  }
  input.close();

  cout << "final result: " << result << endl;

  return 0;
}