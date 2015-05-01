/*Names: Kathleen Kusworo, Gary Qian, Sarah Sukardi, Matthew Tan
  Course: Intermediate Programming (AS.600.120)
  Date: 5/01/2015 (First Deadline), 5/08/2015 (Final Deadline)
  Assignment: Final Project-- Skip-Bo
  JHEDs: kkuswor1, gqian1, ssukard1, mtan13
  Email: (JHED)@jhu.edu
*/

#include "Player.h"
#include "Deck.h"
#include <vector>

using std::vector;

class Display {
  friend class AI;
  friend class DisplayTest;
  
  vector<int> buildTop;
  
 public:
  void display(Player* player, vector<Build*> build, int num);
  
  void display(AI player, vector<Build*> build, int num); 
  
  void change(Player* player, int num);
  
  void intro();
  
 private:
  string convert(int num);
  string convert(int num, Build build);

};
