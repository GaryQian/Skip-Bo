#include "Game.h"
#include <iostream>
#include <fstream>

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::getline;

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
    if(name.substr(0,2) == "AI"){
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

Game::Game() {}

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

void Game::load_game(string filename){

  std::ifstream inFile(filename);
  int num;
  int numPlayers;
  int numMoves;
  string name;
  vector<int> hand;
  vector<int> set;
  vector<vector<int>> discard;
  vector<int> stock;


  inFile > numPlayers;

  while((inFile > num) != -1){
    draw.push_back(num);
  }

  for(int i = 0; i < 4; i++){
    while((inFile>num) != -1){
      build[i].push_back(num);
    }
  }

  build.resize(4);

  for(int i = 0; i < numPlayers; i++){
    inFile > name;

    while((inFile > num)!= -1){
      hand.push_back(num);
    }

    for(int i = 0; i < 4;){
      if((inFile > num) != -1){
        discard[i].push_back(num);
      }
      else{
        ++i;
      }
    }

    while((inFile > num)!= -1){
      stock.push_back(num);
    }

    players.push_back(new Player(name, hand, discard, stock));
    hand.clear();
    discard.clear();
    stock.clear();
  }

  inFile >> numMoves;

  for(int i = 0; i < numMoves; i++){
    Move m;
    inFile >> m.playerNum;
    inFile >> m.source;
    inFile >> m.dest;
    move.push_back(m);
  }

  inFile >> turn;
}

void Game::process(string input){
  if (input.length() < 4){
    cout << "Invalid input" << endl;
    return;
  }

  char source = input.at(0);
  Move m;

  if (source == 's'){
    input = input.substr(1);
    m.source == s;
    m.index = 0;
    m.value = players[turn%players.size()].getStock()[0];
  }
  else if (source == 'd'){
    m.source = source;
    m.index = (input.at(1) - '0')-1;
    if (index > 3){
      cout << "invalid index" << endl;
      return;
    }
    input = input.substr(2);
    m.value = players[turn%players.size()].getDiscard()[m.index][0];
  }
  else if (source == 'h'){
    m.source = source;
    m.index = (input.at(1) - '0')-1;
    if (index > 4){
      cout << "invalid index" << endl;
      return;
    }
    input = input.substr(2);
    m.value = players[turn%players.size()].getHand()[m.index];
  }
  else{
    cout << "Invalid card source" << endl;
    return;
  }

  if (input.at(0) != " "){
    cout << "source and destination must be separated with a single whitespace"\
	 << endl;
    return;
  }

  char dest  = input.substr(1,0);
  int destIndex = 0;

  if (dest == 'b' || dest == 'd'){
    m.dest = dest;
    destIndex = (input.at(2) - '0')-1;

    if (destIndex > 3){
      cout << "Invalid index " << endl;
      return;
    }

    m.destIndex = destIndex;
  }
  else{
    cout << "Invalid destination" << endl;
    return;
  }
  
  if (dest == 'b' && m.value != 0){
    if (build[destIndex]%12 != value - 1){
      cout << "Invalid move" << endl;
    }
  }

  this.play(m);
  return;
}

void Game::play(Move m){
  
}

bool Game::AIPlaying() {
	return players.at(turn%players.size()).isAI();
	
}
  
Player Game::getPlayer() {
	
	return players.at(turn%players.size());
}
