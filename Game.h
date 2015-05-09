/*
  Names: Kathleen Kusworo, Gary Qian, Sarah Sukardi, Matthew Tan
  Course: Intermediate Programming (AS.600.120)
  Date: 5/01/2015 (First Deadline), 5/08/2015 (Final Deadline)
  Assignment: Final Project-- Skip-Bo
  JHEDs: kkuswor1, gqian1, ssukard1, mtan13
  Email: (JHED)@jhu.edu

  This class contains the general game board (which contains the
  players, the build piles, the draw pile, and the players' cards. It
  also handles the user's input move and error-checks if they are
  valid
*/
#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include "Player.h"
#include "Move.h"
#include <stdexcept>

class Game {
  friend class GameTest;
 private:
  std::vector<Player*> players;//stores vector of HumanPlayers and AI
  std::vector<Build*> build;//contains 4 instances of Build class
  Draw* draw;//an instance of the Draw class
  int turn;//represents the turn number
  int numMove;
  int totalMove;
  
 public:
  //regular constructor
  Game(std::vector<std::string> names, int stockSize = 0, 
       std::vector<int> arrangement = {}); 
  
  //regular destructor
  ~Game();

  //constructor that sets every variable to 0 or NULL
  Game();
  
  //This method increments turn 
  void nextTurn();

  //refills current players hand if hand is empty. Also refills deck if less than 5 cards remain
  void refill();

  //checks if stock of player whose turn just ended is 0
  bool hasEnded() const;

  //saves the game by writing all data into a file whose name is specified by the string parameter
  void save_game(string filename) const;

  //loads a previous game by reading all the data from a file whose name is specified by the string parameter. May throw exception if file not found
  void load_game(string filename) throw (std::exception);

  //takes a line of input and creates a move struct out of the data in the line. May throw exception if input is invalid
  void process(string input);

  //Calls the move method of the player whose turn it is and passes the Move struct as a parameter
  void play(Move m);

  //Checks if current player is AI
  bool AIPlaying() const;

  //Returns a pointer to the current player
  Player* getPlayer() const;
  
  //Returns a pointer to the next player
  Player* getNextPlayer() const;
  
  //returns the index of the current player
  int getPlayerNumber();
  
  //returns the index of the next player
  int getNextPlayerNumber();
  
  //return the build vector
  vector<Build*> getBuild();

  //Checks hand and stock of current player and the build pile to see if there are valid moves remaining 
  std::vector<Move*> canMove() const;

  //checks if num is found within the vector of ints
  bool contains(vector<int> vec, int num) const;

  //get the current move number
  int getNumMove();

  //undo the previous move by loading the saved state called move_<num>
  //where <num> is the # of the previous move
  void undo(int num);

  //redo the previous move by loading the saved stated called move_<num>
  //where <num> is the # of the next move
  void redo(int num);
  
  //get all the Player instances in Game
  std::vector<Player*> getPlayers();
};

#endif
