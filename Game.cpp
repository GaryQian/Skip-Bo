#include "Game.h"
#include <iostream>
#include <fstream>

using std::cout;
using std::endl;
using std::vector;
using std::string;

Game::Game(vector<string> names){
  Draw d = new Draw(); 
  int stockSize = 0;
  string name;
  turn = 0;

  if (names.size() < 5){
    stockSize = 30;
  }
  else{
    stockSize = 20;
  }

  while(names.size()){
    name = names.last();
    if(name.substr(0,3) == "AI "){
      players.push_back(new AI(name, d.take(stockSize)));
    }
    else{
      players.push_back(new Player(name, d.take(stockSize)));
    }
    names.pop();
  }

  draw = d;

  for(int i = 0; i < 4; i++){
    build.push_back(new Build());
  }
}

void Game::nextTurn(){
  turn++;
}

bool Game::hasEnded(){
  return players[turn%players.size()].hasWon();
}

void Game::save_game(){
  string filename;

  cout << "Save as:" << endl;
  std::getline(cin, filename);
  std::ofstream outFile(filename);
  
}
