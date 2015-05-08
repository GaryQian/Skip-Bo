/*Names: Kathleen Kusworo, Gary Qian, Sarah Sukardi, Matthew Tan
  Course: Intermediate Programming (AS.600.120)
  Date: 5/01/2015 (First Deadline), 5/08/2015 (Final Deadline)
  Assignment: Final Project-- Skip-Bo
  JHEDs: kkuswor1, gqian1, ssukard1, mtan13
  Email: (JHED)@jhu.edu
*/

#include "Game.h"
#include "Exception.h"
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

const char* SaveException::what() const throw(){
  return "You have chosen to save game.\n";
}

const char* GameEndException::what() const throw(){
  return "Game End.";
}

Game::Game() {
  draw = new Draw();
  turn = 0;
  
  //Game() is used for loading a game, so the saved state
  //is when a user is prompted to make a move. Thus, numMove
  //and totalMove is 1
  numMove = 1;
  totalMove = 1;
}


//destructor of Game class. Deletes dynamically allocated players and builds as well as the draw pile
Game::~Game() {
  for (unsigned long i = 0; i < players.size(); i++){
    delete players.at(i);
  } 
  for (unsigned long i = 0; i < build.size(); i++){
    delete build.at(i);
  }
  delete draw;
}


//usual constructor of Game
Game::Game(vector<string> names, int stockSize, vector<int> arrangement){ 
  string name;
  turn = 0;
  draw = new Draw();

  //shuffle draw pile
  draw->shuffle(arrangement);
  
  //if stockSize is 0, that means user has chosen to use default values
  if(stockSize == 0){
    if (names.size() >= 5){
      stockSize = 20;
    }
    else stockSize = 30;
  }

  //initialize the players
  for(unsigned long i = 0; i < names.size(); i++){
    name = names[i];
    
    Stock s;
    draw->move(s, stockSize);

    //Regardless of whether user specifies AI or not, adds a Player class to the vector players
    if(name.substr(0,2) == "AI"){
      players.push_back(new AI(name, draw, &build, s));
    }
    else{
      players.push_back(new HumanPlayer(name, draw, &build, s));
    }
  }

  //initialize build piles
  for(int i = 0; i < 4; i++){
    build.push_back(new Build());
  }

  //This constructor is used for a new game, so no moves have been made
  numMove = 0;
  totalMove = 0;
}

void Game::nextTurn(){
  //increment turn, # of current move, and set total moves to be equal
  //to numMove (since totalMove is the totalMove of the current move
  //path, NOT the accmulated moves
  turn++;
  numMove++;
  totalMove = numMove;
}

void Game::refill(){
  //if draw pile has less cards than what we want to draw, refill it
  if (5 - getPlayer()->getHand().getSize() > draw->getSize()){
    //find the amount of leftover cards
    int left = draw->getSize();
    
    //move cards from build pile to draw pile
    for (int i = 0; i < 4; i++){
      build[i]->move(*draw, left);
    }
  }
  //draw cards for player
  getPlayer()->drawCards();
}

bool Game::hasEnded() const{
  //can't win at first turn
  if (turn == 1){
    return false;
  }
  else{
    //check if current player has won
    return getPlayer()->hasWon();
  }
}

void Game::save_game(string filename) const{
  int numP = players.size();
  std::ofstream outFile(filename);

  //writes all variables to a file
  outFile << numP << endl;
  
  outFile << *draw << " " << -1 << endl;

  //-1 is the sentinel value that separates different build/discard piles
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

  outFile << endl << turn << endl;

  outFile.close();
}

//loads a game from the data in a text file. May be called on an empty game or a current game with dynamically allocated variables, all of which will be deleted before being overwritten
void Game::load_game(string filename) throw (std::exception){
  std::ifstream inFile(filename);
  
  int num;           //generic card value variable
  int numPlayers;    //num of players
  int numMoves;      //total number of moves (not to be confused with
		     //Game's numMove)
  string name;       //player name
  vector<int> set;   //set of numbers

  //read all variables from the file
  inFile >> numPlayers;
  inFile >> num;

  //clears draw pile before overwriting
  draw->clear();

  while(num != -1){
    *(draw)+=num;
    inFile >> num;
  }

  //clears current build pile before overwriting
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

  //clears players before overwriting
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
 
  inFile >> turn;
  inFile.close();
}

//this is the general method which parses the user input into a move struct which the player class can then process easily
void Game::process(string input){
  //if user chooses to save, throw SaveException()
  if (input.substr(0,4) == "save" || input.substr(0,4) == "Save"){
    string filename;
    cout << "Save as: " << endl;
    getline(std::cin, filename);
    save_game(filename);
    throw SaveException();
  }

  //if user chooses to undo
  if (input.substr(0,4) == "undo" || input.substr(0,4) == "Undo"){
    undo(numMove - 1);
    return;
  }

  //if redo
  if (input.substr(0,4) == "redo" || input.substr(0,4) == "Redo"){
    redo(numMove + 1);
    return;
  }

  //if invalid input length
  if (input.length() < 4) {
    throw std::invalid_argument("Invalid input length\n");
  }

  //analyze text otherwise
  char source = input.at(0);
  Move* m = new Move();

  //if moving from stock pile,
  if (source == 's'){
    //process with the Move class
    input = input.substr(1);
    m->source = source;
    m->sourceIndex = 0;
    m->value = getPlayer()->getStock().getTop();
    if (input.at(0) != ' ') {
      delete m;
      throw std::invalid_argument("Stock does not take an index\n");
    }
  }
  //else if moving from discard pile
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
  //else if moving from hand
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
  //else if invalid source
  else {
    delete m;
    throw std::invalid_argument("Unknown card source\nNote: possible sources are (h = hand, s = stock, d = deck)\n");
  }

  //if invalid whitespace
  if (input.at(0) != ' ' || input.at(1) == ' '){ 
    delete m;
    throw std::invalid_argument("Source and destination must be separated by a single whitespace\n");
  }
  if (input.size() < 3){
    delete m;
    throw std::invalid_argument("Invalid input length\n");
  }

  //now check destination
  char dest  = input.at(1);
  int destIndex = 0;

  //if destination is build pile or discard pile, error-check for index
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
  this->play(*m);
  return;
}

//Modifies Player's cards based on the move provided
void Game::play(Move m){
  getPlayer()->move(m);
  numMove++;
  totalMove = numMove;
  if (hasEnded()){
    throw GameEndException();
  }
}

//Checks whether current player is AI
bool Game::AIPlaying() const{
  return getPlayer()->isAI();	
}

//returns pointer to current player  
Player* Game::getPlayer() const{
  return players.at((turn-1)%players.size());
}

//returns pointer to next player
Player* Game::getNextPlayer() const{
  return players.at((turn)%players.size());
}

//returns a vector of Move pointers that represent all possible/valid moves of the player
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

//returns the index of the current player in the players vector
int Game::getPlayerNumber() {
  return (turn-1)%players.size();
}

//returns the index of the next player in the players vector
int Game::getNextPlayerNumber() {
  return (turn)%players.size();
}

//returns a vector of Build piles
vector<Build*> Game::getBuild() {
  return build;
}

//return how many moves have been made so far
int Game:: getNumMove(){
  return numMove;
}

void Game::undo(int num){  
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

void Game::redo(int num){
  //can't exceed total moves in the current move path
  if(num > totalMove) throw std::invalid_argument("Can't redo!\n");  
  
  //otherwise, load the next move
  ostringstream oss;
  oss << "move_" << num;
  load_game(oss.str());
  numMove = num;
}

//returns vector of Player pointers
vector<Player*> Game::getPlayers() {
  return players;
}

