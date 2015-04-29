#include "Move.h"
#include <sstream>

Move::Move(){}

Move::Move(int p, int v, char s, char d, int sI, int dI): player(p), value(v), source(s), dest(d), sourceIndex(sI), destIndex(dI){}

std::string Move::toString(){
  std::ostringstream oss;
  
  oss << player << " " << value << " " << source << " " << dest << " " << sourceIndex << " " << destIndex << " ";
  return oss.str();
}
