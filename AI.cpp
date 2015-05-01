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
#include <sstream>


using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::ostringstream;

AI::AI(string name, Draw* draw, vector<Build*>* build, Stock stock) {
	this->draw = draw;
	this->name = name;
	this->build = build;
	this->stock = stock;
	for(int i = 0; i < 4; i++){
	  discard.push_back(new Discard());
	}
	seed = time(NULL);
	isAnAI = true;
}

AI::AI(string name, Draw* draw, vector<Build*>* build, Stock stock, Hand hand, vector<Discard*> discard){
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
	vector<int> validNums;
	for (int i = 0; i < 4; ++i) {
		validNums.push_back(build->at(i)->getSize()%12 + 1);
	}
	vector<string*> moves;
	string* temp;
	for (int i = 0; i < hand.getSize(); ++i) {
		//check for skipbo
		if (hand.at(i) == 0) {
			for (int j = 1; j < 5; j++) {
				temp = new string("h");
				*temp += convert(i + 1);
				*temp += " b";
				*temp += convert(j);
				moves.push_back(temp);
			}
		}
		else if (contains(validNums, hand.at(i))) {
			temp = new string("h");
			*temp += convert(i + 1);
			*temp += " b";
			*temp += convert(find(validNums, hand.at(i)) + 1);
			moves.push_back(temp);
		}
	}
	
	for (int i = 0; i < 4; ++i) {
		//check for skipbo
		if (discard[i]->getTop() == 0) {
			for (int j = 1; j < 5; j++) {
				temp = new string("h");
				*temp += convert(i + 1);
				*temp += " b";
				*temp += convert(j);
				moves.push_back(temp);
			}
		}
		else if (contains(validNums, discard[i]->getTop())) {
			temp = new string("d");
			*temp += convert(i + 1);
			*temp += " b";
			*temp += convert(find(validNums, discard[i]->getTop()) + 1);
			moves.push_back(temp);
		}
	}
	
	if (contains(validNums, stock.getTop())) {
	  temp = new string("s b");
		for (int i = 0; i < 5; i++) {
			//check for skipbo
			if (stock.getTop() == 0) {
				for (int j = 1; j < 5; j++) {
				  //temp = new string("s");
				  //	*temp += " b";
					*temp += convert(j);
					moves.push_back(temp);
				}
			}
			else if (contains(validNums, stock.getTop()))
				*temp += convert(find(validNums, stock.getTop()) + 1);
			break;
		}
		for (int i = 0; i < (int) moves.size(); ++i) {
			delete moves.at(i);
		}
		string temp2(*temp);
		delete temp;
		return temp2;
	}
	
	//PICK RANDOM MOVE/BEST MOVE HERE
	srand(seed);
	seed++;
	int ran;
	if (moves.empty()) {
		ran = rand() % hand.getSize() + 1;
		temp = new string("h");
		*temp += convert(ran);
		*temp += " d";
		ran = rand() % 4 + 1;
		*temp += convert(ran);
		cout << *temp;
		std::this_thread::sleep_for(std::chrono::milliseconds(300));	
		string temp2(*temp);
		delete temp;
		for (int i = 0; i < (int) moves.size(); ++i) {
			delete moves.at(i);
		}
		return temp2;
	}
	
	ran = rand() % moves.size();
	string keep(*(moves.at(ran)));
	for (int i = 0; i < (int) moves.size(); ++i) {
		delete moves.at(i);
	}
	//wait so that AI does not move instantaneously
	cout << keep << endl;
	
	std::this_thread::sleep_for(std::chrono::milliseconds(400));	
	
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
  for(int i = 0; i < 4; i++){
    delete discard.at(i);
  }
}

string AI::convert(int num) {
	if (num < 0) {
		return " ";
	}
	ostringstream temp;
	temp << num;
	return temp.str();
}
