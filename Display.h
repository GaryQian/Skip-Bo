#include "Player.h"
#include "Deck.h"

class Display {
  
 public:
  void display(Player player, vector<Build> build, int num);
  
  void display(AI player, vector<Build> build, int num); 
  
 private:
  string convert(int num);

};
