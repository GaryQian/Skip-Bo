#include "Player.h"
#include "Deck.h"
#include "Display.h"
#include "AI.h"
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>


using std::string;
using std::vector;

AI::AI(string name, Draw* draw, vector<Build>* build, Stock stock) {
  Player(name, draw, build, stock);
	seed = time(NULL);
	isAnAI = true;
}

AI::AI(string name, Draw* draw, vector<Build>* build, Stock stock, Hand hand, vector<Discard> discard){
  Player(name, draw, build, stock, hand, discard);
  seed = time(NULL);
  isAnAI = true;
}

string AI::getMove() {
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
			temp += " b";
			temp += Display.comvert(find(validNums, hand.at(i));
			moves.push_back(temp);
		}
	}
	
	for (int i = 0; i < 4; ++i) {
		if (contains(validNums, discard[i].getTop())) {
			temp = new string("d");
			temp += convert(i + 1);
			temp += " b";
			temp += Display.comvert(find(validNums, hand.at(i));
			moves.push_back(temp);
		}
	}
	
	if (contains(validNums, stock.getTop())) {
		temp = new string("s");
		temp += " b";
		temp += Display.comvert(find(validNums, hand.at(i));
		moves.push_back(temp);
	}
	
	//PICK RANDOM MOVE/BEST MOVE HERE
	srand(seed);
	seed++;
	int rand = rand() % moves.size();
	string keep = string(moves.at(rand));
	for (int i = 0; i < moves.size(); ++i) {
		delete moves.at(i);
	}
	return moves.at(rand);
	
	
	///////////////
}

bool AI::contains(vector<int> vec, int num) {
	if (num == 0) return true;
	for (int j = 0; j < vec.size(); ++j) {
		if (num == vec.at(j)) {
			return true;
		}
	}
	return false;
}

int AI::find(vector<int> vec, int num) {
	if (num == 0) return -1;
	for (int j = 0; j < vec.size(); ++j) {
		if (num == vec.at(j)) {
			return j;
		}
	}
	return -1;
}
