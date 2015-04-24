#include "Player.h"
#include "SkipBoFuncs.h"
#include <iostream>
#include <string>
#include <algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::string;

int main(){
	vector<int> deck = createDeck();
	shuffle(deck);
	
	Game game;
	
	string save;
	string temp;
	cout << "Welcome to Skip-Bo!" << endl;
	cout << "Would you like to load a saved game?" << endl;
	
	cin >> save;
	std::transform(save.begin(), save.end(), save.begin(), ::tolower);
	if (save == "yes" || save == "y" || save == "ye" || save == "1" || save.at(0) == 'y' || save.at(0) = '1') {
		cout << "Please enter the savefile name:" << endl;
		cin >> temp;
		game = new Game();
		game.load_game(temp);
	}
	else {
		int numPlayers;
		cout << "How many players? (Enter Integer):" << endl;
		cin >> numPlayers;
	}

	
	//player playerList[numPlayers];
	//for(int i = 1; i <= numPlayers; ++i){
	//  cout << "Enter player " << i << "'s name: " << endl;
	
	//}
}
