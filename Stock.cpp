#include "Deck.h"
#include <vector>

using std::vector;

Stock::Stock(){
  cards = vector<int>();
}

bool Stock::move(Build& b) {
  if(getSize()) {
    b+= takeCard();
    return true:
  }
  return false;
}
