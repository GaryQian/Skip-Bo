#include "Game.h"
#include <iostream>
#include <fstream>

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::getline;

Game::Game() {
  turn = 0;
}

Game::~Game() {
  for (unsigned long i = 0; i < players.size(); i++){
    delete players[i];
  } 
}

Game::Game(vector<string> names, vector<int> arrangement){ 
  int stockSize = 0;
  string name;
  turn = 0;

  draw.shuffle(arrangement);

  if (names.size() < 5){
    stockSize = 30;
  }
  else{
    stockSize = 20;
  }
  
  for(unsigned long i = 0; i < names.size(); i++){
    name = names[i];
    
    Stock s;
    draw.move(s, stockSize);

    if(name.substr(0,3) == "AI "){
      players.push_back(new AI(name, &draw, &build, s));
    }
    else{
      players.push_back(new HumanPlayer(name, &draw, &build, s));
    }
  }

  for(int i = 0; i < 4; i++){
    build.push_back(Build());
  }
}

void Game::nextTurn(){
  turn++;
  if (5 - getPlayer()->getHand().getSize() > draw.getSize()){
    vector<int> left;
    left.resize(draw.getSize());
    
    for(int i = draw.getSize()-1; i >= 0 ; i--){
      left[i] = draw.takeCard();
    }

    for (int i = 0; i < 4; i++){
      build[i].move(draw);
    }

    draw+=left;
  } 
  getPlayer()->drawCards();
}

bool Game::hasEnded(){
  return getPlayer()->hasWon();
}

void Game::save_game(string filename){
  int numP = players.size();
  std::ofstream outFile(filename);

  outFile << numP << endl;
  
  for(int i = 0; i < numP; i++){
    outFile << players[i]->getName() << endl;
  }
  
  outFile << draw.toString() << endl;

  for(int i = 0; i < 4; i++){
    outFile << build[i].toString() << -1 << " ";
  }
  outFile << endl;

  for(int i = 0; i < numP; i++){
    outFile << players[i]->getHand().toString() << endl;
    
    for(int j = 0; j < 4; j++){
      outFile << (players[i]->getDiscard())[j].toString() << -1 << " ";
    }
    outFile << endl;

    outFile << players[i]->getStock().toString() << endl;
  }

  outFile << move.size() << endl;

  for(unsigned long i = 0; i < move.size(); i++){
    outFile << move[i].player << " " << move[i].value << " " << move[i].source << " " << move[i].sourceIndex << " " << move[i].destIndex << " " << move[i].dest << " ";
  }
  outFile << endl << turn << endl;
}

void Game::load_game(string filename){

  std::ifstream inFile(filename);
  int num;
  int numPlayers;
  int numMoves;
  string name;
  vector<int> set;
  
  inFile >> numPlayers;
  inFile >> num;

  while(num != -1){
    draw+=num;
    inFile >> num;
  }

  build.resize(4);

  for(int i = 0; i < 4; i++){
    inFile >> num;
    while(num != -1){
      build[i] += num;
      inFile >> num;
    }
  }

  for(int i = 0; i < numPlayers; i++){
    Stock* s = new Stock();
    Hand* h = new Hand();
    vector<Discard> discard;
    discard.resize(4);
    
    inFile >> name;
    inFile >> num;
    while(num != -1){
      *h+=num;
      inFile >> num;
    }

    for(int i = 0; i < 4;){
      inFile >> num;
      if(num != -1){
        discard[i]+=num;
      }
      else{
        ++i;
      }
    }
    
    inFile >> num;
    while(num != -1){
      *s += num;
      inFile >> num;
    }

    if (name.substr(0,3) == "AI "){
      players.push_back(new AI(name, &draw, &build, *s, *h, discard));
    }
    else {
      players.push_back(new HumanPlayer(name, &draw, &build, *s, *h, discard));
    }
    
  }

  inFile >> numMoves;

  for(int i = 0; i < numMoves; i++){
    Move m;
    inFile >> m.player;
    inFile >> m.value;
    inFile >> m.source;
    inFile >> m.sourceIndex;
    inFile >> m.destIndex;
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
    m.source = source;
    m.sourceIndex = 0;
    m.value = getPlayer()->getStock().getTop();
  }
  else if (source == 'd'){
    m.source = source;
    m.sourceIndex = (input.at(1) - '0')-1;
    if (m.sourceIndex > 3){
      cout << "invalid index" << endl;
      return;
    }
    input = input.substr(2);
    m.value = getPlayer()->getDiscard()[m.sourceIndex].getTop();
  }
  else if (source == 'h'){
    m.source = source;
    m.sourceIndex = (input.at(1) - '0')-1;
    if (m.sourceIndex > 4){
      cout << "invalid index" << endl;
      return;
    }
    input = input.substr(2);
    m.value = getPlayer()->getHand().at(m.sourceIndex);
  }
  else{
    cout << "Invalid card source" << endl;
    return;
  }

  if (input.at(0) != ' '){
    cout << "source and destination must be separated with a single whitespace"<< endl;
    return;
  }

  char dest  = input.at(1);
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
    if (build.at(destIndex).getTop()%12 != m.value - 1){
      cout << "Invalid move" << endl;
    }
  }

  this->play(m);
  return;
}

//Modifies Player's cards based on the move provided
void Game::play(Move m){
  getPlayer()->move(m);
}

bool Game::AIPlaying() {
  return getPlayer()->isAI();	
}
  
Player* Game::getPlayer() {
  return players.at((turn-1)%players.size());
}

bool Game::canMove() {
	vector<int> validNums;
	for (int i = 0; i < 4; ++i) {
	  validNums.push_back(build[i].getSize()%12 + 1);
	}
	
	for (int i = 0; i < getPlayer()->getHand().getSize(); ++i) {
	  if (contains(validNums, getPlayer()->getHand().at(i))) {
	    return true;
	  }
	}
	return false;
}

bool Game::contains(vector<int> vec, int num) {
	if (num == 0) return true;
	for (unsigned long j = 0; j < vec.size(); ++j) {
		if (num == vec.at(j)) {
			return true;
		}
	}
	return false;
}

 
