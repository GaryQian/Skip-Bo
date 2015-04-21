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
	
	vector<Build> build;
	
	Game(vector<string> names) {//copy this code into the implementation .cpp later
		build.push_back(new Build());
		build.push_back(new Build());
		build.push_back(new Build());
		build.push_back(new Build());
		for (int i  = 0; i < names.size(); ++i) {
			if (false) { //check if it is an AI
				players.push_back(new AI(names[i]));
			}
			players.push_back(new Player(names[i]));
		}
		
	}

};