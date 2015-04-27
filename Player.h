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
  vector<Discard> discard;
  bool isAnAI;

  //reference to higher level data
  vector<Build>* build;
	
  Draw* draw;

  //Constructor
  Player(string name, Draw* draw, vector<Build>* build, Stock stock);
  Player(string name, Draw* draw, vector<Build>* build, Stock stock, Hand hand, vector<Discard> discard);
  Player();
  
  friend class HumanPlayer;
  friend class AI;

 public:	
  //Methods
  void deal();
  bool move(Move yourMove);
  bool hasWon();
  //  bool playCard(Deck a, Deck b);
  //  bool playCard(Deck b, int num);
  string getName();
  Hand getHand();
  vector<Discard> getDiscard();
  Stock getStock();
  bool isAI();
  
  virtual string getMove() = 0;
};

class HumanPlayer: public Player {

 public:
  HumanPlayer(string name, Draw* draw, vector<Build>* build, Stock stock);
  HumanPlayer(string name, Draw* draw, vector<Build>* build, Stock stock, Hand hand, vector<Discard> discard);
  string getMove();
  //AI operator AI();

};

class AI: public Player {
  int seed;

 public:
  AI(string name, Draw* draw, vector<Build>* build, Stock stock);
  AI(string name, Draw* draw, vector<Build>* build, Stock stock, Hand hand, vector<Discard> discard);
  string getMove();
  bool contains(vector<int> vec, int num);
  int find(vector<int> vec, int num);
  //HumanPlayer operator HumanPlayer();
};

#endif
