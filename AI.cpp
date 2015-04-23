#include "Player.h"
#include "Draw.h"
#include "Build.h"
#include "Deck.h"
#include "Display.h"
#include "AI.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

AI::AI(string name, Draw* draw, vector<Build>* build) {
	Player(name, draw, build);
}

string AI::calculateMove() {
	vector<int> validNums;
	for (int i = 0; i < 4; ++i) {
		if (*build[i].getTop() != -1) {
			validNums.push_back(*build[i].getTop() + 1);
		}
	}
	vector<string> moves;
	string temp;
	for (int i = 0; i < hand.getSize(); ++i) {
		if (contains(validNums, hand.at(i))) {
			temp = new string("h");
			temp += convert(i + 1);
			moves.push_back(temp);
		}
	}
	
	for (int i = 0; i < 4; ++i) {
		if (contains(validNums, discard[i].getTop())) {
			temp = new string("d");
			temp += convert(i + 1);
			moves.push_back(temp);
		}
	}
	
	if (contains(validNums, stock.getTop())) {
		temp = new string("d");
		moves.push_back(temp);
	}
	
	//PICK RANDOM MOVE/BEST MOVE HERE
	
	
	
	///////////////
}

bool AI::contains(vector<int> vec, int num) {
	if (num == 0) return true;
	for (int j = 0; j < vec.size(); ++j) {
		if (hand.at(i) == vec.at(j)) {
			return true;
		}
	}
	return false;
}