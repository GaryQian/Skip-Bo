#include "Player.h"

#include <string>
#include <vector>

using std::string;
using std::vector;

//Constructors for player
Player::Player(string name, Draw* draw, vector<Build>* build, Stock stock) {
  this->draw = draw;
  this->name = name;
  this->build = build;
  this->stock = stock;
  
  //  deal();
  isAnAI = false;
}

Player::Player(string name, Draw* draw, vector<Build>* build, Stock stock, Hand hand, vector<Discard> discard) {
  this->draw = draw;
  this->name = name;
  this->build = build;
  this->stock = stock;
  this->hand = hand;
  this->discard = discard;

<<<<<<< Updated upstream
  deal();

 public:
=======
  //  deal();
>>>>>>> Stashed changes
  isAnAI = false;
}

bool Player::move(Move yourMove) {
  //source card is stockpile
  if (yourMove.source == 's') {  
    //destination of card is build 
    if (yourMove.dest == 'b') {
      //Loops until the top card of build is skip-bo or the current-card - 1
      int i = 0;
      while((build->at(i).getTop() != (yourMove.value - 1)) || (build->at(i).getTop() != 0)) {
	i++;
      }
      //Moves the card to the correct build pile
      stock.move(build->at(i));
    }
    //destination of card is discard
    else if (yourMove.dest == 'd') {
      //Moves the card to the discard pile provided by user 
     stock.move(discard.at(yourMove.destIndex));
    }
  }

  //source card is discard
  else if (yourMove.source == 'd') {
    //Destination must be a build pile
    int i = 0;
    while((build->at(i).getTop() != (yourMove.value - 1)) || (build->at(i).getTop() != 0)) {
      i++;
    }
    //Moves from the discard pile provided by user to the correct build pile
    discard.at(yourMove.sourceIndex).move(build->at(i));
  }

  //source card is hand 
  else {
    if (yourMove.dest == 'b') {
      int i = 0;
      while((build->at(i).getTop() != (yourMove.value - 1)) || (build->at(i).getTop() != 0)) {
	i++;
      }
      //Moves from hand card provided by user to the correct build pile  
      hand.move(build->at(i), yourMove.sourceIndex);
    }
    else if (yourMove.dest == 'd') {
      //Moves from the hand card to the discard pile whose index is provided by the user
      hand.move(discard.at(yourMove.destIndex), yourMove.sourceIndex);
    }
  }

  //all exceptions should have been handled if this method is called, so there is no need to return false
  return true;
}

//Returns if the player has won
bool Player::hasWon() {
  if (stock.isEmpty()) {
    return true;
  }
  return false;
}

//These methods are not necessary anymore
/*
bool Player::playCard(Deck a, Deck b) {
  if (a.move(b)) {
    return true;
  }
  return false;
}

bool Player::playCard(Deck b, int num) {
  if (hand.move(b, num)) {
    return true;
  }
  return false;
}
*/

//////////Accessor methods///////////

string Player::getName() {
  return name;
}

Hand Player::getHand() {
  return hand;
}

vector<Discard> Player::getDiscard() {
  return discard;
}

Stock Player::getStock() {
  return stock;
}

bool Player::isAI() {
  return isAnAI;
}
