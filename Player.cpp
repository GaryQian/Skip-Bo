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

void Player::deal() {
	stock += draw.take(30);
}