#include "Hand.h"
#include <vector>

using std::vector;

Hand::Hand(){
  size = 5;
}

int Hand::takeCard(int index){
  int chosenCard = cards[index-1];
  cards.erase(cards.begin() + index - 1);
  size = cards.size();
  return chosenCard;
}

bool Hand::move(Deck& d, int index){
  if(index - 1 < size){
    d += takeCard(index);
    return true;
  }
  else return false;
}
