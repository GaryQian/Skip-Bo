#include "Player.h"
#include "Deck.h"
#include "Display.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

class AI: public Player {
	
  int seed;
	
 public:
  
  AI(string name, Draw* draw, vector<Build>* build, Stock* stock);

  AI(string name, Draw* draw, vector<Build>* build, Stock stock, Hand hand, vector<Discard> discard);
  
  string getMove();
  
  bool contains(vector<int> vec, int num);
  
  int find(vector<int> vec, int num);
	
};
