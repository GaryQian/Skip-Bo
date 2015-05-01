/*Names: Kathleen Kusworo, Gary Qian, Sarah Sukardi, Matthew Tan
  Course: Intermediate Programming (AS.600.120)
  Date: 5/01/2015 (First Deadline), 5/08/2015 (Final Deadline)
  Assignment: Final Project-- Skip-Bo
  JHEDs: kkuswor1, gqian1, ssukard1, mtan13
  Email: (JHED)@jhu.edu
*/

#include "Deck.h"
#include <vector>

using std::vector;

Stock::Stock(){
  cards = vector<int>();
}

void Stock::move(Deck& deck){
  if(isEmpty()) throw std::logic_error("Deck is empty.\n");
  
  int card = takeCard();
  try {
    deck += card;
  }
  catch(std::logic_error & e) {
    *this += card;
    throw e;
  }
}

void Stock::operator += (int value) throw (std::invalid_argument){
  if(getSize() == 30) 
    throw std::invalid_argument("Can't have more than 30 cards in Stock pile!\n");
  Deck::operator += (value);
}

void Stock::operator += (vector<int> list) throw (std::invalid_argument){
  if((getSize() + list.size()) > 30) 
    throw std::invalid_argument("Can't have more than 30 cards in Stock pile!\n");
  Deck::operator += (list);
}

Stock::~Stock() {
	
}

