#include "Player.h"
#include "Deck.h"
#include <vector>

using std::vector;

class Display {
	friend class AI;
	friend class DisplayTest;

public:
	/*
	Displays the game board from all the parameters
	*/
	void display(Player* player, vector<Build*> build, int num);
	/*
	Displays the game board from all the parameters if the player passed in is an AI
	*/
	void display(AI player, vector<Build*> build, int num); 
	/*
	Displays the Change player screen
	*/
	void change(Player* player, int num);
	/*
	Displays the intro title Logo
	*/
	void intro();

private:
	/*
	Helper method that takes in a number and converts it into a string of that number
	*/
	string convert(int num);
	/*
	Helper method that takes in a number and Build Pile and returns the top card, ignoring skipbo cards
	*/
	string convert(int num, Build build);

};
