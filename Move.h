#ifndef MOVE_H
#define MOVE_H

typedef struct Move {

  int player;    
  int value;
  char source;
  char dest;
  int sourceIndex;
  int destIndex;
Move(int p, int v, char s, char d, int sI, int dI): player(p), value(v), source(s), dest(d), sourceIndex(sI), destIndex(dI){};
  Move(){};
} Move;

#endif
