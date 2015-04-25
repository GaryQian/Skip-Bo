#include "Player.h"
#include "Draw.h"
#include "Build.h"
#include "Deck.h"
#include "Display.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

class AI: public Player {
	
	int seed;
	
	AI(string name, Draw* draw, vector<Build>* build);
	
	string getMove();
	
	bool contains(vector<int> vec, int num);
	
	int find(vector<int> vec, int num);
	
};
