/*
  Names: Kathleen Kusworo, Gary Qian, Sarah Sukardi, Matthew Tan
  Course: Intermediate Programming (AS.600.120)
  Date: 5/01/2015 (First Deadline), 5/08/2015 (Final Deadline)
  Assignment: Final Project-- Skip-Bo
  JHEDs: kkuswor1, gqian1, ssukard1, mtan13
  Email: (JHED)@jhu.edu

  This class represents the Hand pile.
*/

#include "Deck.h"
#include <vector>

using std::vector;

Hand::Hand(){
  cards = vector<int>();
}

int Hand::takeCard(int index) throw(std::invalid_argument, std::logic_error){
  //error checking
  if(isEmpty()) throw std::logic_error("Hand is empty.\n");
  if(index < 0 || index >= getSize()){
    throw std::invalid_argument("Invalid index\n");
  }

  //take chosen card, then erase that slot
  int chosenCard = cards[index];
  cards.erase(cards.begin() + index);
  return chosenCard;
}

void Hand::move(Deck& deck, int index) throw (std::invalid_argument,
					      std::logic_error){ 
  if(isEmpty()){
    throw std::logic_error("Hand is empty.\n");
  }
  deck += takeCard(index);
}

void Hand::operator += (int value) throw (std::invalid_argument) {
  //if user tries to take more than 5 cards, or if Hand is already full
  //throw an exception
  if(getSize() == 5)
    throw std::invalid_argument("Shouldn't draw more than five cards!\n");

  Deck::operator += (value);
}

void Hand::operator += (vector<int> list) throw (std::invalid_argument) {
  if(getSize() + list.size() > 5)
    throw std::invalid_argument("Shouldn't draw more than five cards!\n");

  //if pass error checking, call super operator
  Deck::operator += (list);
}

Hand::~Hand() {
	
}
