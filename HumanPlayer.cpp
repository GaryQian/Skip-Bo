#include "HumanPlayer.h"
#include <string>

using std::string;
using std::cin;


HumanPlayer::HumanPlayer(string name, Draw* draw, vector<Build>* build) {
	Player(name, draw, build);
	seed = time(NULL);
	isAI = false;
}

string HumanPlayer::getMove() {
	string temp;
	cin >> temp;
	return temp;
}