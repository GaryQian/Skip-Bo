#include <vector>
#include <string>
#include "Player.h"
#include "Build.h"
#include "Display.h"
#include "Move.h"
#include "AI.h"


using std::vector;
using std::string;

class Game {

	vector<Player> players;
	
	vector<Move> move;
	
	Display display;
	
	Build build;
	
	Game(vector<string> names) : build(), display() {
		
		for (int i  = 0; i < names.size(); ++i) {
			if (false) {
				players.push_back(new AI(names[i]));
			}
			players.push_back(new Player(names[i]));
		}
		
	}

};