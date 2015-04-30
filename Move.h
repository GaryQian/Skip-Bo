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
