/*
  Names: Kathleen Kusworo, Gary Qian, Sarah Sukardi, Matthew Tan
  Course: Intermediate Programming (AS.600.120)
  Date: 5/01/2015 (First Deadline), 5/08/2015 (Final Deadline)
  Assignment: Final Project-- Skip-Bo
  JHEDs: kkuswor1, gqian1, ssukard1, mtan13
  Email: (JHED)@jhu.edu

  This abstract class represents a Player and the card piles
  associated with each player (e.g. Hand, Stock, Discard). It handles
  basic Player moves, like drawing cards into their Hand and processing 
  a movement made by the user. Also throws TurnEndException if the player
  discards a card.
*/

#include "Player.h"
#include "Exception.h"
#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <cassert>

using std::string;
using std::vector;

const char* TurnEndException::what() const throw(){
  return "Turn end.";
}

Player::~Player(){}

void Player::drawCards(){
  draw->move(hand, 5 - hand.getSize());  
}

void Player::move(Move yourMove){
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

  if (yourMove.dest == 'd') throw TurnEndException();
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
