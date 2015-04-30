#include "Player.h"
#include "Deck.h"
#include <vector>

using std::vector;

class Display {
  friend class AI;
  
  vector<int> buildTop;
  
 public:
  void display(Player* player, vector<Build*> build, int num);
  
  void display(AI player, vector<Build*> build, int num); 
  
  void change(Player* player, int num);
  
 private:
  string convert(int num);
  string convert(int num, Build build);

};
