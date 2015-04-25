#include <string>
#include "Player.h"

class HumanPlayer: public Player {

 public:
  HumanPlayer(string name, Draw* draw, vector<Build>* build, Stock* stock);
	
  HumanPlayer(string name, Draw* draw, vector<Build>* build, Stock stock, Hand hand, vector<Discard> discard);

  string getMove();

};
