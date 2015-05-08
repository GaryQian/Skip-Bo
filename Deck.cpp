/*Names: Kathleen Kusworo, Gary Qian, Sarah Sukardi, Matthew Tan
  Course: Intermediate Programming (AS.600.120)
  Date: 5/01/2015 (First Deadline), 5/08/2015 (Final Deadline)
  Assignment: Final Project-- Skip-Bo
  JHEDs: kkuswor1, gqian1, ssukard1, mtan13
  Email: (JHED)@jhu.edu
*/

#include "Deck.h"
#include <cstdlib>

using std::vector;
using std::string;
using std::ostringstream;
using std::ostream;
using std::iterator;

Deck::~Deck(){}

int Deck::getSize() const {
  return cards.size();
}

int Deck::takeCard() throw (std::logic_error){
  if(isEmpty()) throw std::logic_error("Deck is empty.\n");
  
//get top card, pop back element
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

int Deck::at(int num) {
  return cards.at(num);
}

void Deck::move(Deck& d) throw(std::logic_error){
  d += takeCard();
}

void Deck::operator +=(int value) throw (std::invalid_argument){
  if(value < 0 || value > 12) 
    throw std::invalid_argument("Invalid card value.\n");
  //otherwise, add card
  cards.push_back(value);
}

void Deck::operator +=(vector<int> list) throw (std::invalid_argument){
  //error check first
  vector<int>::const_iterator it;
  for(it = list.begin(); it < list.end(); it++){
    if (*it < 0 || *it > 12)
      throw std::invalid_argument("Invalid card value.\n");
  }

  //if no invalid card values, then append the list to cards
  vector<int> newCards;
  newCards.reserve(getSize() + list.size());
  newCards.insert(newCards.end(), cards.begin(), cards.end());
  newCards.insert(newCards.end(), list.begin(), list.end());
  cards = newCards;
}

string Deck::toString() const {
  vector<int>::const_iterator it;
  ostringstream oss;

  //list all elements, separated by a space
  for(it = cards.begin(); it < cards.end(); it++) {
    oss << *it << " ";
  }
  return oss.str();
}

std::ostream& operator << (std::ostream& os, const Deck& d) {
  os << d.toString();
  return os;
}
