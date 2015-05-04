/*Names: Kathleen Kusworo, Gary Qian, Sarah Sukardi, Matthew Tan
  Course: Intermediate Programming (AS.600.120)
  Date: 5/01/2015 (First Deadline), 5/08/2015 (Final Deadline)
  Assignment: Final Project-- Skip-Bo
  JHEDs: kkuswor1, gqian1, ssukard1, mtan13
  Email: (JHED)@jhu.edu
*/

#include "Game.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <stdexcept>

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::getline;
using std::ostringstream;

Game::Game() {
  draw = new Draw();
  turn = 0;
  numMove = 1;
}

Game::~Game() {
  for (unsigned long i = 0; i < players.size(); i++){
    delete players.at(i);
  } 
  for (unsigned long i = 0; i < move.size(); i++){
    delete move.at(i);
  }
  for (unsigned long i = 0; i < build.size(); i++){
    delete build.at(i);
  }
  delete draw;
}

Game::Game(vector<string> names, vector<int> arrangement){ 
  int stockSize = 0;
  string name;
  turn = 0;
  draw = new Draw();

  draw->shuffle(arrangement);

  if (names.size() < 5){
    stockSize = 30;
  }
  else{
    stockSize = 20;
  }
  
  for(unsigned long i = 0; i < names.size(); i++){
    name = names[i];
    
    Stock s;
    draw->move(s, stockSize);

    if(name.substr(0,2) == "AI"){
      players.push_back(new AI(name, draw, &build, s));
    }
    else{
      players.push_back(new HumanPlayer(name, draw, &build, s));
    }
  }

  for(int i = 0; i < 4; i++){
    build.push_back(new Build());
  }

  numMove = 1;
}

void Game::nextTurn(){
  turn++;
  numMove = 1;
  totalMove = 1;
  system("rm move_*");
}

void Game::refill(){
  if (5 - getPlayer()->getHand().getSize() > draw->getSize()){
    int left = draw->getSize();
    
    for (int i = 0; i < 4; i++){
      build[i]->move(*draw, left);
    }
  }
  getPlayer()->drawCards();
}

bool Game::hasEnded() const{
  if (turn == 1){
    return false;
  }
  else{
    return players.at((turn-2)%players.size())->hasWon();
  }
}

void Game::save_game(string filename) const{
  int numP = players.size();
  std::ofstream outFile(filename);

  outFile << numP << endl;
  
  outFile << *draw << " " << -1 << endl;

  for(int i = 0; i < 4; i++){
    outFile << *(build[i]) << -1 << " ";
  }
  outFile << endl;

  for(int i = 0; i < numP; i++){
    outFile << players[i]->getName() << endl;
    outFile << players[i]->getHand() << " " << -1 <<endl;
    
    for(int j = 0; j < 4; j++){
      outFile << *((players[i]->getDiscard()).at(j)) << -1 << " ";
    }
    outFile << endl;

    outFile << players[i]->getStock() << " " << -1 << endl;
  }

  outFile << move.size() << endl;

  for(unsigned long i = 0; i < move.size(); i++){
    outFile << move[i]->toString();
  }
  outFile << endl << turn << endl;
  outFile.close();
}

void Game::load_game(string filename) throw (std::exception){
  try{
    std::ifstream inFile(filename);
  
    int num;
    int numPlayers;
    int numMoves;
    string name;
    vector<int> set;

    inFile >> numPlayers;
    inFile >> num;

    draw->clear();

    while(num != -1){
      *(draw)+=num;
      inFile >> num;
    }
 
    for(int i = 0; i < (int)build.size(); i++){
      delete build.at(i);
    }
    build.clear();
 
    for(int i = 0; i < 4; i++){
      Build* b = new Build();
      inFile >> num;
      while(num != -1){
	*b += num;
	inFile >> num;
      }
      build.push_back(b);
    }

    for(int i = 0; i < (int)players.size(); i++){
      delete players.at(i);
    }
  
    players.clear();
    for(int i = 0; i < numPlayers; i++){
      Stock* s = new Stock();
      Hand* h = new Hand();
      vector<Discard*> discard;
      for(int i = 0; i < 4; i++){
	discard.push_back(new Discard());
      }
      std::getline(inFile, name);
      std::getline(inFile, name);
  
      inFile >> num;
      while(num != -1){
	*h+=num;
	inFile >> num;
      }

      for(int i = 0; i < 4; i++){
	inFile >> num;
	while(num != -1){
	  *(discard.at(i))+=num;
	  inFile >> num;
	}
      }   
    
      inFile >> num;
      while(num != -1){
	*s += num;
	inFile >> num;
      }

      if (name.substr(0,2) == "AI"){
	players.push_back(new AI(name, draw, &build, *s, *h, discard));
      }
      else {
	players.push_back(new HumanPlayer(name, draw, &build, *s, *h, discard));
      }
      delete s;
      delete h;
    }

    inFile >> numMoves;

    for(int i = 0; i < numMoves; i++){
      Move* m = new Move();
      inFile >> m->player;
      inFile >> m->value;
      inFile >> m->source;
      inFile >> m->dest;
      inFile >> m->sourceIndex;
      inFile >> m->destIndex;

      move.push_back(m);
    }
 
    inFile >> turn;
    inFile.close();
  }
  catch (std::exception & e){
    throw e;
  }
}


void Game::process(string input){
  if (input.substr(0,4) == "save" || input.substr(0,4) == "Save"){
    string filename;
    cout << "Save as: " << endl;
    getline(std::cin, filename);
    save_game(filename);
    throw 's';
  }

  if (input.substr(0,4) == "undo" || input.substr(0,4) == "Undo"){
    undo(numMove - 1);
    return;
  }

  if (input.substr(0,4) == "redo" || input.substr(0,4) == "Redo"){
    redo(numMove + 1);
    return;
  }

  if (input.length() < 4) throw std::invalid_argument("Invalid input length\n");

  char source = input.at(0);
  Move* m = new Move();

  if (source == 's'){
    input = input.substr(1);
    m->source = source;
    m->sourceIndex = 0;
    m->value = getPlayer()->getStock().getTop();
    if (input.at(0) != ' ') {
      delete m;
      throw std::invalid_argument("Stock does not take an index\n");
    }
  }
  else if (source == 'd'){
    m->source = source;
    m->sourceIndex = (input.at(1) - '0')-1;
    if (m->sourceIndex > 3 || m->sourceIndex < 0){
      delete m;
      throw std::invalid_argument("Invalid discard pile index\n");
    }
    input = input.substr(2);
    m->value = getPlayer()->getDiscard()[m->sourceIndex]->getTop();
  }
  else if (source == 'h'){
    m->source = source;
    m->sourceIndex = (input.at(1) - '0')-1;
    if (m->sourceIndex < 0 || m->sourceIndex > getPlayer()->getHand().getSize() - 1){
      delete m;
      throw std::invalid_argument("Invalid hand index\n");
    }

    input = input.substr(2);
    m->value = getPlayer()->getHand().at(m->sourceIndex);
  }
  else {
    delete m;
    throw std::invalid_argument("Unknown card source\nNote: possible sources are (h = hand, s = stock, d = deck)\n");
  }


  if (input.at(0) != ' ' || input.at(1) == ' '){ 
    delete m;
    throw std::invalid_argument("Source and destination must be separated by a single whitespace\n");
  }
  if (input.size() < 3){
    delete m;
    throw std::invalid_argument("Invalid input length\n");
  }

  char dest  = input.at(1);
  int destIndex = 0;

  if (dest == 'b' || dest == 'd'){
    m->dest = dest;
    destIndex = (input.at(2) - '0')-1;

    if (destIndex > 3 || destIndex < 0){
      delete m;
      throw std::invalid_argument("Invalid index for destination\n");
    }
    m->destIndex = destIndex;
  }
  else {
    delete m;
    throw std::invalid_argument("Unknown card destination\nNote: possible destinations are (d = discard, b = build pile)");
  }

  if (dest == 'b' && m->value != 0){
    if (build.at(destIndex)->getSize()%12 != m->value - 1){
      delete m;
      throw std::invalid_argument("Source and destination do not match");
    }
  }
  
  if (dest == 'd' && source == 's'){
    delete m;
    throw std::invalid_argument("Stock card cannot be moved to discard pile\n");
  }
  
  m->player = (turn-1)%players.size();
  move.push_back(m);
  this->play(*m);
  return;
}

//Modifies Player's cards based on the move provided
void Game::play(Move m){
  getPlayer()->move(m);
  numMove++;
  totalMove = numMove;
  clear_move_path(numMove);
}

bool Game::AIPlaying() const{
  return getPlayer()->isAI();	
}
  
Player* Game::getPlayer() const{
  return players.at((turn-1)%players.size());
}

Player* Game::getNextPlayer() const{
  return players.at((turn)%players.size());
}

vector<Move*> Game::canMove() const{
  vector<Move*> validMoves;
  int p = (turn-1)%players.size();
  
  //checks all possible cards in hand
  for (int i = 0; i < getPlayer()->getHand().getSize(); i++){
    for (int j = 0; j < 4; j++){
      //check all build piles if card in hand can be placed there
      if (!getPlayer()->getHand().at(i) || getPlayer()->getHand().at(i) == build.at(j)->getSize()%12+1){
	validMoves.push_back(new Move(p, getPlayer()->getHand().at(i), 'h', 'b', i, j));   
      }     
    }
  }
  
  //check all 4 discard piles
  for (int i = 0; i < 4; i++){
    //check if can be placed in any build pile
    for (int j = 0; j < 4; j++){
      if (!getPlayer()->getDiscard().at(i)->getTop() || getPlayer()->getDiscard().at(i)->getTop() == build.at(j)->getSize()%12+1){
	validMoves.push_back(new Move(p, getPlayer()->getDiscard().at(i)->getTop(), 'd', 'b', i, j));
      }
    }
  }
  
  //checks if stock can be placed in build pile
  for (int i = 0; i < 4; i++){
    if (!getPlayer()->getStock().getTop() || getPlayer()->getStock().getTop()== build.at(i)->getSize()%12+1){
      validMoves.push_back(new Move(p, getPlayer()->getStock().getTop(), 's', 'b', 0, i));
    }
  }
  
  return validMoves;
}

int Game::getPlayerNumber() {
  return (turn-1)%players.size();
}

int Game::getNextPlayerNumber() {
  return (turn)%players.size();
}

vector<Build*> Game::getBuild() {
  return build;
}

int Game:: getNumMove(){
  return numMove;
}

void Game::undo(int num) throw (std::invalid_argument){  
  //if the player tries to undo at the start of their turn, throw exception
  //and don't decrement numMove
  if(num == 0) 
    throw std::invalid_argument("Can't undo - this is the start of your turn!\n");
  
  //else, load the previous game state
  //and update numMove by decrementing it (b/c now we're back at a
  //previous game state)
  ostringstream oss;
  oss << "move_" << num;
  load_game(oss.str());
  numMove = num;
}

void Game::redo(int num) throw(std::exception){
  if(num > totalMove) throw std::invalid_argument("Can't redo!\n");  
  ostringstream oss;
  oss << "move_" << num;
  try {
    load_game(oss.str());
    numMove = num;
  }
  catch(std::invalid_argument & e){
    throw e; //std::invalid_argument("Can't redo!\n");
  } 
  oss.str("");
  oss.clear();
}

void Game::clear_move_path(int numMove){
  ostringstream oss;
  //cout << numMove + 1;
  oss << "rm move_*[" << numMove + 1 << "-9]";
  string s = oss.str();
  
  system(s.c_str());
}

