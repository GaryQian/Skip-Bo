#include "Player.h"
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
  isAnAI = false;
}

HumanPlayer::HumanPlayer(Player& player) {
	Player(player.name, player.draw, player.build, player.stock, player.hand, player.discard);
	seed = time(NULL);
	isAnAI = false;
}


string HumanPlayer::getMove() {
	string temp;
	cin >> temp;
	return temp;
}

/*operator AI() {
	return AI(name, draw, build, stock, hand, discard);
}*/