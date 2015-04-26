#include <vector>
#include <string>
#include "HumanPlayer.h"
#include "Move.h"
#include "AI.h"

class Game {
 private:
  std::vector<Player> players;
  std::vector<Move> move;
  std::vector<Build> build;
  Draw draw;
  int turn;
  
 public:
  //Constructor
  Game(std::vector<std::string> names); 
  
  Game();

  //Mutator functions
  void nextTurn();
  
  bool hasEnded();
  
  void save_game(string filename);
  
  void load_game(string filename);
  
  void process(string input);
  
  void play(Move m);
  
  bool AIPlaying();
  
  HumanPlayer getPlayer();
  
  bool canMove();
  
  int getPlayerNumber();
  
  bool contains(vector<int> vec, int num);
};
