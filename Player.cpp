#include "Player.h"

#include <string>
#include <vector>

using std::string;
using std::vector;


Player::Player(string name, Draw* draw, vector<Build>* build) {
  this->draw = *draw;
  this->name = name;
  this->build = build;
  deal();	
}

//do we have to accomodate for when there are more than 4 players; in which there would be 20 cards/player?
void Player::deal() {
  stock += draw.take(30);
}
