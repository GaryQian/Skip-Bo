#include "Player.h"
#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <cassert>

using std::string;
using std::vector;

Player::~Player(){}

void Player::drawCards(){
  draw->move(hand, 5 - hand.getSize());  
}

void Player::move(Move yourMove) throw (int) {
  //source card is stockpile
  if (yourMove.source == 's') {
    //the only destination is build
    stock.move(*(build->at(yourMove.destIndex)));
  }

  //source card is discard
  else if (yourMove.source == 'd') {
    //Moves from the discard pile provided by user to the correct build pile
    discard.at(yourMove.sourceIndex)->move(*(build->at(yourMove.destIndex)));
  }

  //source card is hand 
  else {
    if (yourMove.dest == 'b') {
      //Moves from hand card provided by user to the correct build pile  
      hand.move(*(build->at(yourMove.destIndex)), yourMove.sourceIndex);
    }
    else if (yourMove.dest == 'd') {
      //Moves from the hand card to the discard pile whose index is provided by the user
      hand.move(*(discard.at(yourMove.destIndex)), yourMove.sourceIndex);
    }
  }

  if (yourMove.dest == 'd') throw 1;
}

//Returns if the player has won
bool Player::hasWon() {
  if (stock.isEmpty()) {
    return true;
  }
  return false;
}

//////////Accessor methods///////////

string Player::getName() {
  return name;
}

Hand Player::getHand() {
  return hand;
}

vector<Discard*> Player::getDiscard() {
  return discard;
}

Stock Player::getStock() {
  return stock;
}

bool Player::isAI() {
  return isAnAI;
}
