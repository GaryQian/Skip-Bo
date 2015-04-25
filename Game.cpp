#include "Game.h"
#include <iostream>
#include <fstream>

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::getline;

Game::Game(vector<string> names){
  Draw* d = new Draw(); 
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
    name = names.back();
    
    Stock* s = new Stock();
    for(int i = 0; i < stockSize; i++){
      d->Deck::move(*s);
    }

    if(name.substr(0,3) == "AI "){
      players.push_back(*(new AI(name, d, &build, s)));
    }
    else{
      players.push_back(*(new HumanPlayer(name, d, &build, s)));
    }
    names.pop_back();
  }

  draw = *d;

  for(int i = 0; i < 4; i++){
    build.push_back(*(new Build()));
  }
}

void Game::nextTurn(){
  turn++;
  if (5 - players[(turn-1)%players.size()].getHand().getSize() > draw.getSize()){
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
}

bool Game::hasEnded(){
  return players[(turn-1)%players.size()].hasWon();
}

void Game::save_game(string filename){
  int numP = players.size();
  std::ofstream outFile(filename);

  outFile << numP << endl;
  
  for(int i = 0; i < numP; i++){
    outFile << players[i].getName() << endl;
  }
  
  outFile << draw.toString() << endl;

  for(int i = 0; i < 4; i++){
    outFile << build[i].toString() << -1 << " ";
  }
  outFile << endl;

  for(int i = 0; i < numP; i++){
    outFile << players[i].getHand().toString() << endl;
    
    for(int j = 0; j < 4; j++){
      outFile << (players[i].getDiscard())[j].toString() << -1 << " ";
    }
    outFile << endl;

    outFile << players[i].getStock().toString() << endl;
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
      players.push_back(*(new AI(name, &draw, &build, *s, *h, discard)));
    }
    else {
      players.push_back(*(new HumanPlayer(name, &draw, &build, *s, *h, discard)));
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
    m.value = players[(turn-1)%players.size()].getStock().getTop();
  }
  else if (source == 'd'){
    m.source = source;
    m.sourceIndex = (input.at(1) - '0')-1;
    if (m.sourceIndex > 3){
      cout << "invalid index" << endl;
      return;
    }
    input = input.substr(2);
    m.value = players[(turn-1)%players.size()].getDiscard()[m.sourceIndex].getTop();
  }
  else if (source == 'h'){
    m.source = source;
    m.sourceIndex = (input.at(1) - '0')-1;
    if (m.sourceIndex > 4){
      cout << "invalid index" << endl;
      return;
    }
    input = input.substr(2);
    m.value = players[turn%players.size()].getHand()[m.sourceIndex];
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
    if (build[destIndex]%12 != value - 1){
      cout << "Invalid move" << endl;
    }
  }

  this.play(m);
  return;
}

void Game::play(Move m){
  players[turn%players.size()]
}

bool Game::AIPlaying() {
	return players.at(turn%players.size()).isAI();
	
}
  
Player Game::getPlayer() {
	
	return players.at(turn%players.size());
}

bool Game::canMove() {
	vector<int> validNums;
	for (int i = 0; i < 4; ++i) {
		if (*(getPlayer().build).at(i).getTop() != -1) {
			validNums.push_back(*build[i].getTop() + 1);
		}
	}
	vector<string> moves;
	string temp;
	for (int i = 0; i < hand.getSize(); ++i) {
		if (contains(validNums, *(getPlayer().build).hand.at(i))) {
			temp = new string("h");
			temp += convert(i + 1);
			moves.push_back(temp);
		}
	}
	
	for (int i = 0; i < 4; ++i) {
		if (contains(validNums, *(getPlayer().build).at(i).getTop())) {
			temp = new string("d");
			temp += convert(i + 1);
			moves.push_back(temp);
		}
	}
	int movenum = moves.size();
	for (int i = 0; i < moves.size(); ++i) {
		delete moves.at(i);
	}
	if (movenu.size == 0) return false;
	return true;
}

bool Game::contains(vector<int> vec, int num) {
	if (num == 0) return true;
	for (int j = 0; j < vec.size(); ++j) {
		if (hand.at(i) == vec.at(j)) {
			return true;
		}
	}
	return false;
}
