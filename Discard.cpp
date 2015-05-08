/*
  Names: Kathleen Kusworo, Gary Qian, Sarah Sukardi, Matthew Tan
  Course: Intermediate Programming (AS.600.120)
  Date: 5/01/2015 (First Deadline), 5/08/2015 (Final Deadline)
  Assignment: Final Project-- Skip-Bo
  JHEDs: kkuswor1, gqian1, ssukard1, mtan13
  Email: (JHED)@jhu.edu

  This class represents the discard pile.
*/

#include "Deck.h"
#include <vector>

using std::vector;

Discard::Discard(){
  cards = vector<int>();
}

void Discard::move(Build& build){
  if(isEmpty()) throw std::logic_error("Deck is empty.\n");

  int card = takeCard();

  //need to be able to return card if this attempt failed,
  //AND notify the user that it failed - hence the try
  //catch block here
  try {
    build += card;
  } 
  //if not valid, return the card to discard pile
  catch(std::invalid_argument & e){
    *this += card;
    throw e;
  }
}
