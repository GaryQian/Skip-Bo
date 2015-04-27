#include "Game.h"
#include "Display.h"
#include <iostream>
#include <string>
#include <algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::string;

int main(){
	Game* game;
	string save;
	string input;
	vector<string> names;
	int players;
	Display d;
	//Prompts user to enter in a game
	cout << "Welcome to Skip-Bo!" << endl;
	cout << "Would you like to load a saved game?" << endl;

	//Loads the game	
	cin >> save;
	std::transform(save.begin(), save.end(), save.begin(), ::tolower);
	if (save == "yes" || save == "y" || save == "ye" || save == "1" || save.at(0) == 'y' || save.at(0) == '1') {
		cout << "Please enter the savefile name:" << endl;
		cin >> input;
		game = new Game();
		game->load_game(input);
	}
	else {
    	        //Else, begins a new game
		
		cout << "How many players? (Enter Integer):" << endl;
		cin >> players;
		
		names.resize(players);
		
		for(int i = 0; i < players; i++){
			cout << "Enter name of player " << i+1 << ". If player is an AI, prefix with \"AI \"." << endl;
			cin >> names[ i ];
		}
	}	
	game = new Game(names);
	
	while (!game->hasEnded()) {
		game->nextTurn();
		while (game->canMove()) {
		  d.display(*(game->getPlayer()), game->getBuild(), game->getPlayerNumber());
			input = game->getPlayer()->getMove();
			game->process(input);
		}
		
		
	}
	
}
