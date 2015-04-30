#include "Player.h"
#include "Deck.h"
#include "Display.h"
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <chrono>
#include <thread>
#include <sstream>

using std::string;
using std::vector;
using std::cout;
using std::endl;

AI::AI(string name, Draw* draw, vector<Build*>* build, Stock stock) {
	this->draw = draw;
	this->name = name;
	this->build = build;
	this->stock = stock;
	for(int i = 0; i < 4; i++){
	  discard.push_back(new Discard());
	}
	seed = time(NULL);
	isAnAI = true;
}

AI::AI(string name, Draw* draw, vector<Build*>* build, Stock stock, Hand hand, vector<Discard*> discard){
  this->draw = draw;
  this->name = name;
  this->build = build;
  this->stock = stock;
  this->hand = hand;
  this->discard = discard;
  seed = time(NULL);
  isAnAI = true;
}

string AI::getMove() {
        
  vector<string> validMoves;
  std::ostringstream oss;
  for (int i = 0; i < hand.getSize(); ++i) {
    for (int j = 0; j < 4; ++j){
      if (!hand.at(i) || hand.at(i) == build->at(j)->getSize()%12 + 1){
	oss << 'h' << i + 1 << " b" << j+1 << endl;
	validMoves.push_back(oss.str());
	oss.clear();
      } 
      oss << 'h' << i + 1 << " d" << j+1 << endl;
      validMoves.push_back(oss.str());
      oss.clear();
    }
  }
  
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j){
      if (!discard.at(i)->getTop() || discard.at(i)->getTop() == build->at(j)->getSize()%12 + 1){
	oss << 'd' << i + 1 << " " << 'b' << j+1 << endl;
	validMoves.push_back(oss.str());
	oss.clear();
      }
    }
  }
  
  for (int i = 0; i < 4; ++i){
    if (!stock.getTop() || stock.getTop() == build->at(i)->getSize()%12 + 1){
      oss << "s b" << i+1 << endl;
      validMoves.push_back(oss.str());
      oss.clear();
    }
  }
  
  //PICK RANDOM MOVE/BEST MOVE HERE
  srand(seed);
  seed++;
  int ran;
  
  ran = rand() % validMoves.size();
  string keep = string(validMoves.at(ran));
  //wait so that AI does not move instantaneously
  cout << keep << endl;
  
  std::this_thread::sleep_for(std::chrono::milliseconds(300));	
  
  return keep;
  
  
  ///////////////
}

int AI::find(vector<int> vec, int num) {
	if (num == 0) return -1;
	for (int j = 0; j < (int) vec.size(); ++j) {
		if (num == vec.at(j)) {
			return j;
		}
	}
	return -1;
}

AI::~AI() {
  
}
