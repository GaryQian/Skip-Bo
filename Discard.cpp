#include "Deck.h"
#include <vector>

using std::vector;

Discard::Discard(){
  cards = vector<int>();
}

bool Discard::move(Build& build){
  if(getSize()){
    build += takeCard();
    return true;
  }
  return false;
}
