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
  
  Game();

  //Mutator functions
  void nextTurn();
  
  bool hasEnded(0;
  
  void save_game()(string filename);
  
  void load_game(string filename);
  
  void process(string input);
  
  void play(Move m);
  
  bool AIPlaying();
  
  Player getPlayer();
};
