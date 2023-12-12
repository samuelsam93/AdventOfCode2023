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

int* processPull(string* game) {
  string pull;
  int rgb[3] = {0, 0, 0};
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
    if (color == "red"){
      rgb[0] = num_cubes;
    } else if (color == "green") {
      rgb[1] = num_cubes;
    } else if (color == "blue") {
      rgb[2] = num_cubes;
    }
  }
  return rgb;
}

int main() {
  ifstream input;
  input.open("AoC2.txt", ios::in);
  string game;
  int result = 0;
  while (getline(input, game)) {
    int game_number = getGameNumber(&game);
    cout << "game no: " << game_number << "\n";
    cout << "game: " << game << "\n";
    int max_red =0, max_green = 0, max_blue = 0;
    while ((game.length() > 0)) {
      int* game_result = processPull(&game);
      if (*game_result > max_red) {
        max_red = *game_result;
      }
      if (game_result[1] > max_green) {
        max_green = game_result[1];
      }
      if (game_result[2] > max_blue) {
        max_blue = game_result[2];
      }
    }
    cout << "max red: " << max_red << " max green: " << max_green << " max blue: " << max_blue << "\n";
    result += (max_red * max_green * max_blue);
  }
  input.close();

  cout << "final result: " << result << endl;

  return 0;
}