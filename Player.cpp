#include "Player.h"

#include <string>
#include <vector>

#define LESSPLAYERS 30
#define MOREPLAYERS 20

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

bool Player::move(Move yourMove) {
  if (yourMove.source == 'h' || yourMove.source == 'H') {
    //
  }
  else if (yourMove.source == 'd' || yourMove.source == 'D') {
    //
  }
  else /*assumed that source is stock*/ {
    //
  }

  if (yourMove.dest == 'b' || yourMove.dest == 'B') {

  }
  //discard problem: which discard pile to place the card in cannot be encapsulated into a single char
  else if (yourMove.dest == 'd' || yourMove.dest == 'D'){

  }

  return true;
}

bool Player::hasWon() {
  if (stock.isEmpty()) {
    return true;
  }
  return false;
}

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
