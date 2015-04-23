#include "Deck.h"
#include <cstdlib>

using std::vector;
using std::string;
using std::ostringstream;
using std::ostream;
using std::iterator;

int Deck::getSize() {
  return size;
}
/*
int Deck::takeCard(){
  int topCard = getTop();
  cards.pop_back();
  return topCard;
  }*/

int Deck::getTop() {
  return cards[size-1];
}

bool Deck::isEmpty(){
  return size == 0;
}

bool Deck::move(Deck& d){
  if(isEmpty()){
    d += takeCard();
    return true;
  }
  return false;
}

void Deck::operator +=(int value){
  cards.push_back(value);
  size++;
}

void Deck::operator +=(vector<int> list){
  vector<int> newCards;
  newCards.reserve(size + list.size());
  newCards.insert(newCards.end(), cards.begin(), cards.end());
  newCards.insert(newCards.end(), list.begin(), list.end());
  cards = newCards;
}

string Deck::toString() const{
  vector<int>::const_iterator it;
  ostringstream oss;

  for(it = cards.begin(); it < cards.end(); it++){
    oss << *it << " ";
  }
  return oss.str();
}

ostream& operator << (ostream& os, const Deck& d){
  os << d.toString();
  return os;
}
