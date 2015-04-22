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
  Game(std::vector<std::string> names);
  void nextTurn();
};
