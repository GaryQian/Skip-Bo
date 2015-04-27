#include "Deck.h"
#include <math.h>
#include <stdio.h>

using std::vector;

Draw::Draw(){
  //add 144 cards, numbered 1 to 12
  for(int i = 0; i < 12; i++){
    for(int j = 0; j < 12; j++){
      cards.push_back(j+1);
    }
  }  
  //add 18 Skip-Bo wild cards
  for(int i = 0; i < 18; i++){
    cards.push_back(0);
  }
}

void Draw::move(Hand& hand, int num) throw(std::invalid_argument){
  if(getSize() < num) 
    throw std::invalid_argument("Draw pile doesn't have enough cards.\n");

  if(hand.getSize() == 5 || hand.getSize() + num > 5)
    throw std::invalid_argument("Shouldn't draw more than five cards!\n");

  vector<int> toMove;
  //if we have enough cards in the draw pile, take whatever is needed
  
  for(int i = 0; i < num; i++){
    toMove.push_back(takeCard());
  }
  hand += toMove;
}

void Draw::move(Stock& stock, int num) throw(std::invalid_argument){
  if(getSize() < num) 
    throw std::logic_error("Draw pile doesn't have enough cards.\n");

  if(stock.getSize() == 30 || stock.getSize() + num > 30)
    throw std::invalid_argument("Can't have more than 30 cards in Stock pile!\n");

  vector<int> toMove;
  //if we have enough cards in the draw pile, take whatever is needed
  
  for(int i = 0; i < num; i++){
    toMove.push_back(takeCard());
  }
  stock += toMove;
}

void Draw::shuffle(vector<int> arr){
  vector<int> shuffled;
  int last = getSize() - 1;

  //if the user passes in a given arrangement in the form of a vector
  //of integers, use each element of the vector as the index of the
  //card to be added to the new shuffled vector.  else, generate our
  //own randomized arrangement. Basically does the same shuffling
  //method afterwards.
  if(arr.size() > 0){
    vector<int>::const_iterator it;

    for(it = arr.begin(); it < arr.end(); it++){
      //add the card at index indicated by arr to the shuffled vector
      shuffled.push_back(cards[*it]);
      //move the chosen card to the back, and decrement last so that
      //the chosen card can't be re-chosen
      swap(cards[*it], cards[last]);
      last--;
    }
  }
  else{
    srand(time(NULL));
    while(last>0){
      int num = rand() % last;
      shuffled.push_back(cards[num]);
      swap(cards[num],cards[last]);
      last--;
    }
    shuffled.push_back(cards[0]);
  }
  //replace the old vector with the new shuffled one
  cards = shuffled;
}

void Draw::swap(int& a, int& b){
  int temp = b;
  b = a; 
  a = temp;
}
