#include <string>
#include <vector>
#include "Hand.h"
#include "Discard.h"
#include "Draw.h"


using std::string;
using std::vector;

class player {
	string name;
	vector<Hand> hand;
	Stock stock;
	
	vector<Discard> discard;

	//reference to higher level data
	vector<Build>* build;
	Draw* draw;

	player(string name, Draw* draw) { //copy to .cpp file later
		this->draw = *draw;
		this->name = name;

	}  //constructor
};
