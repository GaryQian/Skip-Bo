#include "Deck.h"
#include <cstdlib>

using std::vector;
using std::string;
using std::ostringstream;
using std::ostream;
using std::iterator;

int Deck::getSize() {
  return cards.size();
}

int Deck::takeCard() {
  int topCard = getTop();
  cards.pop_back();
  return topCard;
  }

int Deck::getTop() {
  return cards[getSize() - 1];
}
 
bool Deck::isEmpty() {
  return getSize() == 0;
}

void Deck::operator +=(int value) {
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

void shuffle(vector<int> v){
  vector<int> shuffled;
  int last = getSize();

  //if the user passes in a given arrangement in the form of a vector
  //of integers, use each element of the vector as the index of the
  //card to be added to the new shuffled vector.  else, generate our
  //own randomized arrangement. Basically does the same shuffling
  //method afterwards.
  if(arr.size() > 0){
    vector<int>::const_iterator it;

    for(it = arr.begin(); it < arr.end(); it++){
      //add the card at index indicated by arr to the shuffled vector
      shuffled.push_back(v[*it]);
      //move the chosen card to the back, and decrement last so that
      //the chosen card can't be re-chosen
      swap(v[*it], v[last-1]);
      last--;
    }
  }
  else{
    srand(time(NULL));
    while(last--){
      int num = rand() % last;
      shuffled.push_back(v[num]);
      swap(v[num],v[last-1]);
    }
  }
  //replace the old vector with the new shuffled one
  v = shuffled;
}

void swap(int&a , int& b){
  int temp = b;
  b = a;
  a = temp;
}
