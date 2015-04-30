#include "Player.h"
#include <string>
#include <iostream>

using std::string;
using std::cin;

HumanPlayer::HumanPlayer(string name, Draw* draw, vector<Build*>* build, Stock stock) {
  this->draw = draw;
  this->name = name;
  this->build = build;
  this->stock = stock;
  for(int i = 0; i < 4; i++){
    discard.push_back(new Discard());
  }
  isAnAI = false;

}

HumanPlayer::HumanPlayer(string name, Draw* draw, vector<Build*>* build, Stock stock, Hand hand, vector<Discard*> discard){
  this->draw = draw;
  this->name = name;
  this->build = build;
  this->stock = stock;
  this->hand = hand;
  this->discard = discard;
}

HumanPlayer::~HumanPlayer(){}

/*HumanPlayer::HumanPlayer(Player& player) {
  this->draw = draw;
  this->name = name;
  this->build = build;
  this->stock = stock;
  this->hand = hand;
  this->discard = discard;
}
*/

string HumanPlayer::getMove() {
	string temp;
    	std::getline(cin, temp);
	return temp;
}

/*operator AI() {
	return AI(name, draw, build, stock, hand, discard);
}*/
