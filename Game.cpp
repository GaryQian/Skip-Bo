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

void Game::save_game(string filename){
  int numP = Players.size();
  std::ofstream outFile(filename);

  outFile << numP << endl;
  
  for(int i = 0; i < numP; i++){
    outFile << Players[i].getName() << endl;
  }
  
  outFile << draw.print() << endl;

  for(int i = 0; i < 4; i++){
    outFile << build[i].print() << -1 << " ";
  }
  outFile << endl;

  for(int i = 0; i < numP; i++){
    outFile << Players[i].getHand().print() << endl;
    
    for(int j = 0; j < 4; j++){
      outFile << (Players[i].getDiscard())[j].print() << -1 << " ";
    }
    outFile << endl;

    outFile << Players[i].getStock().print() << endl;
  }

  outFile << move.size() << endl;

  for(int i = 0; i < move.size(); i++){
    outFile << move[i].playerNum << " " << move[i].source << " " << move[i].dest << endl;
  }

  outFile << turn << endl;
}

