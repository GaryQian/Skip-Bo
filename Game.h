#include <vector>
#include <string>
#include "Player.h"
#include "Move.h"
#include <stdexcept>

class Game {
  friend class GameTest;
 private:
  std::vector<Player*> players;//stores vector of HumanPlayers and AI
  std::vector<Move*> move;//stores move structs
  std::vector<Build> build;//contains 4 instances of Build class
  Draw draw;//an instance of the Draw class
  int turn;//represents the turn number
  
 public:
  //regular constructor
  Game(std::vector<std::string> names, std::vector<int> arrangement = {}); 
  
  //regular destructor
  ~Game();

  //constructor that sets every variable to 0 or NULL
  Game();
  
  //This method increments turn and allows next player to draw cards until size of hand is 5. Also refills the draw pile if insufficient cards to refill hand
  void nextTurn();

  //checks if stock of player whose turn just ended is 0
  bool hasEnded() const;

  //saves the game by writing all data into a file whose name is specified by the string parameter
  void save_game(string filename) const;

  //loads a previous game by reading all the data from a file whose name is specified by the string parameter. May throw exception if file not found
  void load_game(string filename);

  //takes a line of input and creates a move struct out of the data in the line. May throw exception if input is invalid
  void process(string input);

  //Calls the move method of the player whose turn it is and passes the Move struct as a parameter
  void play(Move m);

  //Checks if current player is AI
  bool AIPlaying() const;

  //Returns a pointer to the current player
  Player* getPlayer() const;
  
  //returns the index of the current player
  int getPlayerNumber();
  
  //return the build vector
  vector<Build> getBuild();

  //Checks hand and stock of current player and the build pile to see if there are valid moves remaining 
  std::vector<Move*> canMove() const;

  //checks if num is found within the vector of ints
  bool contains(vector<int> vec, int num) const;
};
