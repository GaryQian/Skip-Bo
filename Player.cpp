#include "Player.h"

#include <string>
#include <vector>

#define LESSPLAYERS 30
#define MOREPLAYERS 20

using std::string;
using std::vector;

Player::Player(string name, Draw* draw, vector<Build>* build) {
  this->draw = *draw;
  this->name = name;
  this->build = build;
  deal();
  isAnAI = false;
}

void Player::deal(int playerNum) 
{
  //gives each player 30 cards if there are less than or equal to 4 players
  if (playerNum <= 4 && playerNum >= 1) {
      stock += draw.take(LESSPLAYERS);
  }

  //gives each player 20 cards if there are over 4 players
  if (playerNum > 4) {
    stock += draw.take(MOREPLAYERS);
  }
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
  if (hand.move(Deck b, int num)) {
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

vector<int> Player::getStock() {
  return stock;
}

bool Player::isAI() {
  return isAnAI;
}
