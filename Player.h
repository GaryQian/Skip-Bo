#include <string>
#include <vector>
#include "Deck.h"

using std::string;
using std::vector;

class Player {
  //Instance fields
  string name;	
  Hand hand;       
  Stock theStock;	
  vector<Discard> discard;
  bool isAnAI;

  //reference to higher level data
  vector<Build>* build;
	
  Draw* draw;

  //Constructor
  Player(string name, Draw* draw, vector<Build>* build, Stock theStock);
	
  //Methods
  void deal();
  bool hasWon();
  bool playCard(Deck a, Deck b);
  bool playCard(Deck b, int num);
  string getName();
  Hand getHand();
  vector<Discard> getDiscard();
  Stock getStock();
  bool isAI();
};
