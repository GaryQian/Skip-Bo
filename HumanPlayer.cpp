#include "HumanPlayer.h"
#include <string>

using std::string;
using std::cin;

HumanPlayer::HumanPlayer(string name, Draw* draw, vector<Build>* build, Stock* stock) {
  Player(name, draw, build, stock);
	seed = time(NULL);
	isAI = false;
}

string HumanPlayer::getMove() {
	string temp;
	cin >> temp;
	return temp;
}
