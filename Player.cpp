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

//How to know from Move data which discard/build pile to put dest. card into?
bool Player::move(Move yourMove) {
  if (yourMove.source == 's') {
    if (yourMove.dest == 'b') {
      stock.move(build /*which index?*/);
    }
    else if (yourMove.dest == 'd') {
      stock.move(discard /* which discard pile?*/);
    }
  }
  else if (yourMove.source == 'd') {
    //implementation
  }
  else /*assumed that source is hand*/ {
    hand.takeCard(yourMove.index);

    if (yourMove.dest == 'b') {
      hand.move(build /*which index*/);
    }
    else if (yourMove.dest == 'd') {
      hand.move(discard /*which discard pile*/);
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
