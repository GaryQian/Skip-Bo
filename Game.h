#include <vector>
#include <string>
#include "Player.h"
#include "Build.h"
#include "Display.h"
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

  //Mutator functions
  void nextTurn();
};
