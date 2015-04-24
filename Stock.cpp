#include "Deck.h"
#include <vector>

using std::vector;

Stock::Stock(){
  cards = vector<int>();
}

bool Stock::move(Stock& s) {
  if(getSize()) {
    s += takeCard();
    return true:
  }
  return false;
}
