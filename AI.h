#include "Player.h"
#include "Draw.h"
#include "Build.h"
#include "Deck.h"
#include "Display.h"
#include <string>
#include <vector>

//Add a comment to this line
using std::string;
using std::vector;
 
class AI: public Player {
 
	AI(string name, Draw* draw, vector<Build>* build);
	
	string calculateMove();
	
	bool contains(vector<int> vec, int num);
	
};