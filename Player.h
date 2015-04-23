#include <string>
#include <vector>
#include "Hand.h"
#include "Discard.h"
#include "Draw.h"

using std::string;
using std::vector;

class Player {
  string name;	
  Hand hand;       
  Stock stock;	
  vector<Discard> discard;

  //reference to higher level data
  vector<Build>* build;
	
  Draw* draw;

  Player(string name, Draw* draw, vector<Build>* build) { //copy to .cpp file later
    this->draw = *draw;
    this->name = name;
    this->build = build;
    deal();
  }  //constructor
	
  void deal();
  bool hasWon();
  bool playCard(Deck a, Deck b);
  bool playCard(Deck b, int num);
  string getName();
  Hand getHand();
  vector<Discard> getDiscard();
  vector<int> getStock();
};
