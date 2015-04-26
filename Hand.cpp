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

void Hand::move(Deck& deck, int index) throw (std::invalid_argument,
					      std::logic_error){ 
  if(getSize() == 0){
    throw std::logic_error("Hand is empty.");
  }
  deck += takeCard(index);
}
