#include "Deck.h"
#include <cstdlib>

using std::vector;
using std::string;
using std::ostringstream;
using std::ostream;
using std::iterator;

int Deck::getSize() const {
  return cards.size();
}

int Deck::takeCard() throw (std::logic_error){
  if(isEmpty()) throw std::logic_error("Deck is empty.\n");
  int topCard = getTop();
  cards.pop_back();
  return topCard;
  }

int Deck::getTop() const {
  if(getSize() == 0) return -1;
  return cards[getSize() - 1];
}
 
bool Deck::isEmpty() const {
  return getSize() == 0;
}

void Deck::move(Deck& d) throw(std::logic_error){
  d += takeCard();
}

void Deck::operator +=(int value) throw (std::invalid_argument){
  if(value < 0 || value > 12) 
    throw std::invalid_argument("Invalid card value.\n");
  cards.push_back(value);
}

void Deck::operator +=(vector<int> list) {
  vector<int> newCards;
  newCards.reserve(getSize() + list.size());
  newCards.insert(newCards.end(), cards.begin(), cards.end());
  newCards.insert(newCards.end(), list.begin(), list.end());
  cards = newCards;
}

string Deck::toString() const {
  vector<int>::const_iterator it;
  ostringstream oss;

  for(it = cards.begin(); it < cards.end(); it++) {
    oss << *it << " ";
  }
  return oss.str();
}

std::ostream& operator << (std::ostream& os, const Deck& d) {
  os << d.toString();
  return os;
}
