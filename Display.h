#include "Player.h"
#include "Deck.h"
#include "HumanPlayer.h"
#include "AI.h"

class Display {
    
  static void display(HumanPlayer player, vector<Build> build, int num);
  
  static void display(AI player, vector<Build> build, int num); 
  
  static string convert(int num);

};
