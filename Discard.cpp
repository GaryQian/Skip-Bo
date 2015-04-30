#include "Deck.h"
#include <vector>

using std::vector;

Discard::Discard(){
  cards = vector<int>();
}


void Discard::move(Build& build){
  if(isEmpty()) throw std::logic_error("Deck is empty.\n");
  
  int card = takeCard();
  try {
    build += card;
  } 
  //if not valid, return the card to discard pile
  catch(std::invalid_argument & e){
    *this += card;
    throw e;
  }
}
