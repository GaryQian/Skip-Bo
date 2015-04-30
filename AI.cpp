#include "Player.h"
#include "Deck.h"
#include "Display.h"
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <chrono>
#include <thread>


using std::string;
using std::vector;
using std::cout;
using std::endl;

AI::AI(string name, Draw* draw, vector<Build*>* build, Stock stock) {
	this->draw = draw;
	this->name = name;
	this->build = build;
	this->stock = stock;
	discard.resize(4);
	seed = time(NULL);
	isAnAI = true;
}

AI::AI(string name, Draw* draw, vector<Build*>* build, Stock stock, Hand hand, vector<Discard> discard){
  this->draw = draw;
  this->name = name;
  this->build = build;
  this->stock = stock;
  this->hand = hand;
  this->discard = discard;
  seed = time(NULL);
  isAnAI = true;
}

string AI::getMove() {
	Display d;
	vector<int> validNums;
	for (int i = 0; i < 4; ++i) {
		if (build->at(i)->getTop() != -1) {
		  validNums.push_back(build->at(i)->getTop() + 1);
		}
	}
	vector<string> moves;
	string* temp;
	for (int i = 0; i < hand.getSize(); ++i) {
		if (contains(validNums, hand.at(i))) {
			temp = new string("h");
			*temp += d.convert(i + 1);
			*temp += " b";
			*temp += d.convert(find(validNums, hand.at(i)));
			moves.push_back(*temp);
		}
	}
	
	for (int i = 0; i < 4; ++i) {
		if (contains(validNums, discard[i].getTop())) {
			temp = new string("d");
			*temp += d.convert(i + 1);
			*temp += " b";
			*temp += d.convert(find(validNums, hand.at(i)));
			moves.push_back(*temp);
		}
	}
	
	if (contains(validNums, stock.getTop())) {
		temp = new string("s");
		*temp += " b";
		for (int i = 0; i < 5; i++) {
			if (hand.at(i) == stock.getTop())
				*temp += d.convert(find(validNums, hand.at(i)));
			break;
		}
		moves.push_back(*temp);
	}
	
	//PICK RANDOM MOVE/BEST MOVE HERE
	srand(seed);
	seed++;
	int ran;
	if (moves.empty()) {
		ran = rand() % hand.getSize() + 1;
		temp = new string("h");
		*temp += d.convert(ran);
		*temp += " b";
		ran = rand() % 4 + 1;
		*temp += d.convert(ran);
		cout << *temp;
		return *temp;
	}
	
	ran = rand() % moves.size();
	string keep = string(moves.at(ran));
	for (int i = 0; i < (int) moves.size(); ++i) {
		delete &moves.at(i);
	}
	//wait so that AI does not move instantaneously
	cout << keep << endl;
	
	std::this_thread::sleep_for(std::chrono::milliseconds(300));	
	
	return keep;
	
	
	///////////////
}

bool AI::contains(vector<int> vec, int num) {
	if (num == 0) return true;
	for (int j = 0; j < (int) vec.size(); ++j) {
		if (num == vec.at(j)) {
			return true;
		}
	}
	return false;
}

int AI::find(vector<int> vec, int num) {
	if (num == 0) return -1;
	for (int j = 0; j < (int) vec.size(); ++j) {
		if (num == vec.at(j)) {
			return j;
		}
	}
	return -1;
}

AI::~AI() {
  
}
