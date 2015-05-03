/*Names: Kathleen Kusworo, Gary Qian, Sarah Sukardi, Matthew Tan
Course: Intermediate Programming (AS.600.120)
Date: 5/01/2015 (First Deadline), 5/08/2015 (Final Deadline)
Assignment: Final Project-- Skip-Bo
JHEDs: kkuswor1, gqian1, ssukard1, mtan13
Email: (JHED)@jhu.edu
*/

#include <string>
#include <vector>
#include "Move.h"
#include "Deck.h"
#ifndef PLAYER_H
#define PLAYER_H

using std::string;
using std::vector;

class Player {
	//Instance fields
	string name;	
	Hand hand;       
	Stock stock;	
	vector<Discard*> discard;
	bool isAnAI;

	//reference to higher level data
	vector<Build*>* build;
	
	Draw* draw;  
	friend class HumanPlayer;
	friend class AI;
	friend class DisplayTest;

public:
	//Destructor
	virtual ~Player();
	
	//Methods
	void drawCards();
	void move(Move yourMove) throw (int);
	bool hasWon();
	//  bool playCard(Deck a, Deck b);
	//  bool playCard(Deck b, int num);
	string getName();
	Hand getHand();
	vector<Discard*> getDiscard();
	Stock getStock();
	bool isAI();

	//Pure virtual method that represents the player instance getting a move from a source
	virtual string getMove() = 0;
};

class HumanPlayer: public Player {
	friend class DisplayTest;
public:

	//constructors
	HumanPlayer(string name, Draw* draw, vector<Build*>* build, Stock stock);
	HumanPlayer(string name, Draw* draw, vector<Build*>* build, Stock stock, Hand hand, vector<Discard*> discard);

	//destructor
	~HumanPlayer();
	
	/*
	Reads in a move from cin, and returns it as a string
	*/
	string getMove();
	//AI operator AI();

};

class AI: public Player {
	int seed;
	friend class DisplayTest;
public:
	//constructors
	AI(string name, Draw* draw, vector<Build*>* build, Stock stock);
	AI(string name, Draw* draw, vector<Build*>* build, Stock stock, Hand hand, vector<Discard*> discard);

	//destructor
	~AI();

	/*
	Calculates all valid moves, and picks the best move the AI can make. Returns the move as a string
	*/
	string getMove();

	/*
	Helper method that returns true if the given int num is found in the provided vector, and false otherwise
	*/
	bool contains(vector<int> vec, int num);

	/*
	Helper method that returns returns the index of the num in vector vec
	*/
	int find(vector<int> vec, int num);

	/*
	Helper method that converts a int to a string
	*/
	string convert(int num);
	//HumanPlayer operator HumanPlayer();
};

#endif
