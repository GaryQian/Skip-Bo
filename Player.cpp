#include "Player.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

Player::~Player(){}

void Player::drawCards(){
  while(hand.getSize() < 5){
    draw->move(hand, 5 - hand.getSize());
  }
}

bool Player::move(Move yourMove) throw (int) {
  //source card is stockpile
  if (yourMove.source == 's') {  
    //destination of card is build 
    if (yourMove.dest == 'b') {
      stock.move(build->at(yourMove.destIndex));}
    //destination of card is discard
    else if (yourMove.dest == 'd') {
      //Moves the card to the discard pile provided by user 
     stock.move(discard.at(yourMove.destIndex)); 
    }
  }

  //source card is discard
  else if (yourMove.source == 'd') {
    //Moves from the discard pile provided by user to the correct build pile
    discard.at(yourMove.sourceIndex).move(build->at(yourMove.destIndex));
  }

  //source card is hand 
  else {
    if (yourMove.dest == 'b') {
      //Moves from hand card provided by user to the correct build pile  
      hand.move(build->at(yourMove.destIndex), yourMove.sourceIndex);
    }
    else if (yourMove.dest == 'd') {
      //Moves from the hand card to the discard pile whose index is provided by the user
      hand.move(discard.at(yourMove.destIndex), yourMove.sourceIndex);
    }
  }

  if (yourMove.dest == 'd') throw 1;

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
