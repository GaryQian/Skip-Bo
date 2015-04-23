#include "Hand.h"
#include <vector>

using std::vector;

Hand::Hand(){
  cards = vector<int>();
}

int Hand::takeCard(int index){
  int chosenCard = cards[index-1];
  cards.erase(cards.begin() + index - 1);
  return chosenCard;
}

bool Hand::move(Deck& d, int index){
  if(index - 1 < getSize()){
    d += takeCard(index);
    return true;
  }
  else return false;
}
