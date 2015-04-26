#include "Player.h"

#include <string>
#include <vector>

using std::string;
using std::vector;

Player::Player(string name, Draw* draw, vector<Build>* build, Stock stock) {
  this->draw = draw;
  this->name = name;
  this->build = build;
  this->stock = stock;
  
  deal();
  isAnAI = false;
}

Player::Player(string name, Draw* draw, vector<Build>* build, Stock stock, Hand hand, vector<Discard> discard) {
  this->draw = draw;
  this->name = name;
  this->build = build;
  this->stock = stock;
  this->hand = hand;
  this->discard = discard;

  deal();
  isAnAI = false;
}

//How to know from Move data which discard/build pile to put dest. card into?
bool Player::move(Move yourMove) {

  //////////IMPLEMENTED////////////
  //source card is stockpile
  if (yourMove.source == 's') {  
    if (yourMove.dest == 'b') {
      //Loops until the top card of build is skip-bo or the current-card - 1
      int i = 0;
      while((build->at(i).getTop() != (yourMove.value - 1)) || (build->at(i).getTop() != 0)) {
	i++;
      }
      stock.move(build->at(i));
    }
    else if (yourMove.dest == 'd') {
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
    //Moves from the particular discard pile to the chosen build pile
    discard.at(yourMove.index).move(build->at(i));
  }

  ///////////NOT IMPLEMENTED YET//////////

  //source card is hand 
  else {
    if (yourMove.dest == 'b') {
    int i = 0;
    while((build->at(i).getTop() != (yourMove.value - 1)) || (build->at(i).getTop() != 0)) {
      i++;
    }
    hand.move(build->at(i), yourMove.index);
    }
    else if (yourMove.dest == 'd') {
      hand.move(discard.at(yourMove.destIndex), yourMove.index);
    }
  }
  return true;
}

bool Player::hasWon() {
  if (stock.isEmpty()) {
    return true;
  }
  return false;
}

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
