#include <string>
#include "Player.h"

class HumanPlayer: public Player {
	
	HumanPlayer(string name, Draw* draw, vector<Build>* build);
	
	string getMove();

}