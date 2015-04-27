#include <vector>
#include <string>
#include "Player.h"
#include "Move.h"

class Game {
  friend class GameTest;
 private:
  std::vector<Player*> players;
  std::vector<Move> move;
  std::vector<Build> build;
  Draw draw;
  int turn;
  
 public:
  //Constructor
  Game(std::vector<std::string> names); 
  
  ~Game();

  void nextTurn();

  std::vector<Build> getBuild();
  
  bool hasEnded();
  
  void save_game(string filename);
  
  void load_game(string filename);
  
  void process(string input);
  
  void play(Move m);
  
  bool AIPlaying();
  
  Player* getPlayer();
  
  bool canMove();
  
  int getPlayerNumber();
  
  bool contains(vector<int> vec, int num);
};
