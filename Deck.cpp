#include "Deck.h"
#include <vector>

using std::vector;

Deck::Deck(){
  
}

int Deck::getSize() {
  return size;
}

int Deck::takeCard() {
  int topCard = getTop();
  cards.pop_back();
  return topCard;
}

int Deck::getTop() {
  return cards[size-1];
}

bool Deck::isEmpty(){
  return size == 0;
}

bool Deck::move(Deck b){
  if(isEmpty()){
    b += this -> takeCard();
    return true;
  }
  return false;
}


bool Deck::move(Deck b, int num){
  
  return true;
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

int main(){
  
}
