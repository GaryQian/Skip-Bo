#include "Deck.h"
#include <vector>

using std::vector;

Stock::Stock(){
  cards = vector<int>();
}

void Stock::operator += (int value) throw (std::invalid_argument){
  if(getSize() == 30) throw std::invalid_argument("Stock pile is full!\n");
  Deck::operator += (value);
}

void Stock::operator += (vector<int> list) throw (std::invalid_argument){
  if((getSize() + list.size()) > 30) 
    throw std::invalid_argument("Stock pile is full!\n");
  Deck::operator += (list);
}

