#include "Deck.h"
#include <vector>

using std::vector;

Hand::Hand(){
  cards = vector<int>();
}

int Hand::takeCard(int index) throw(std::invalid_argument){
  if(index < 0 || index >= getSize()){
    throw std::invalid_argument("Invalid index\n");
  }
  int chosenCard = cards[index];
  cards.erase(cards.begin() + index);
  return chosenCard;
}

bool Hand::move(Deck& deck, int index){
  if(index - 1 < getSize()){
    deck += takeCard(index);
    return true;
  }
  else return false;
}
