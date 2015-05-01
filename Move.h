/*Names: Kathleen Kusworo, Gary Qian, Sarah Sukardi, Matthew Tan
  Course: Intermediate Programming (AS.600.120)
  Date: 5/01/2015 (First Deadline), 5/08/2015 (Final Deadline)
  Assignment: Final Project-- Skip-Bo
  JHEDs: kkuswor1, gqian1, ssukard1, mtan13
  Email: (JHED)@jhu.edu
*/

#ifndef MOVE_H
#define MOVE_H
#include <string>

class Move {
 public:
  int player;    
  int value;
  char source;
  char dest;
  int sourceIndex;
  int destIndex;
  Move(int p, int v, char s, char d, int sI, int dI);
  Move();
  ~Move();
  std::string toString();
};

#endif
