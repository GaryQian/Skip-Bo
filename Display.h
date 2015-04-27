#include "Player.h"
#include "Deck.h"

class Display {
  
 public:
  void display(HumanPlayer player, vector<Build> build, int num);
  
  void display(AI player, vector<Build> build, int num); 
  
 private:
  string convert(int num);

};
