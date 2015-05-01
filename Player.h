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

  string getMove();
  //AI operator AI();

};

class AI: public Player {
  int seed;
  friend class DisplayTest;
 public:
  //constructor
  AI(string name, Draw* draw, vector<Build*>* build, Stock stock);
  AI(string name, Draw* draw, vector<Build*>* build, Stock stock, Hand hand, vector<Discard*> discard);

  //destructor
  ~AI();

  string getMove();
  bool contains(vector<int> vec, int num);
  int find(vector<int> vec, int num);
  string convert(int num);
  //HumanPlayer operator HumanPlayer();
};

#endif
