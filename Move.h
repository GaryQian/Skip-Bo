#ifndef MOVE_H
#define MOVE_H
#include <string>

typedef struct Move {

  int player;    
  int value;
  char source;
  char dest;
  int sourceIndex;
  int destIndex;
  Move(int p, int v, char s, char d, int sI, int dI);
  Move();
  std::string toString();
} Move;

#endif
