#include "Deck.h"
#include <vector>

using std::vector;

Discard::Discard(){
  cards = vector<int>();
}

bool Discard::move(Build& b){
  if(getSize()){
    b += takeCard();
    return true;
  }
  return false;
}