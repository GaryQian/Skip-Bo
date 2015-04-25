#ifndef MOVE_H
#define MOVE_H

typedef struct Move {

  int player;    
  int value;
  char source;
  int sourceIndex;
  int destIndex;
  char dest;	

} Move;

#endif
