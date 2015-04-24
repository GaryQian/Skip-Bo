#include <string>
#include "Move.h"

using std::string;

Move::Move(int player, string move) {
	this->player = player;
	this->move = move;
}

int Move::getPlayer() {
	return player;
}

string Move::getMove() {
	return move;
}

char Move::getSource() {
	return move.at(0);
}

int Move::getNumber() {
	return move.at(2);
}

void Move::setPlayer(int num) {
	player = num;
}

void Move::setMove(string str) {
	move = str;
	
}