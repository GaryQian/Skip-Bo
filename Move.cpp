/*
  Names: Kathleen Kusworo, Gary Qian, Sarah Sukardi, Matthew Tan
  Course: Intermediate Programming (AS.600.120)
  Date: 5/01/2015 (First Deadline), 5/08/2015 (Final Deadline)
  Assignment: Final Project-- Skip-Bo
  JHEDs: kkuswor1, gqian1, ssukard1, mtan13
  Email: (JHED)@jhu.edu

  Move contains the details of a move made by the user and contains a
  toString method that converts these details to a string.
*/

#include "Move.h"
#include <sstream>

Move::Move(){}

Move::~Move(){}

Move::Move(int p, int v, char s, char d, int sI, int dI): player(p), value(v), source(s), dest(d), sourceIndex(sI), destIndex(dI){}

std::string Move::toString(){
  std::ostringstream oss;
  
  oss << player << " " << value << " " << source << " " << dest << " " << sourceIndex << " " << destIndex << " ";
  return oss.str();
}
