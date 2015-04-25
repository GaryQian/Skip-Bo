#include "HumanPlayer.h"
#include <string>

using std::string;
using std::cin;


HumanPlayer::HumanPlayer(string name, Draw* draw, vector<Build>* build, Stock* stock) {
  Player(name, draw, build, stock);
	seed = time(NULL);
	isAnAI = false;
}

HumanPlayer::HumanPlayer(string name, Draw* draw, vector<Build>* build, Stock stock, Hand hand, vector<Discard> discard){
  Player(name, draw, build, stock, hand, discard);
  seed = time(NULL);
  isAnAI = true;
}


string HumanPlayer::getMove() {
	string temp;
	cin >> temp;
	return temp;
}
