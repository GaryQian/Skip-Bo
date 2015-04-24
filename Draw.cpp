#include "Deck.h"

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

bool Draw::move(Hand& hand, int num){
  vector<int> toMove;
  //if we have enough cards in the draw pile, take whatever is needed
  if(getSize() > num){
    for(int i = 0; i < num; i++){
      toMove.push_back(takeCard());
    }
    hand += toMove;
    return true;
  }
  //else if draw pile is not empty, but has less than the requested
  //number of cards, just take what remains in the draw pile
  else if(!isEmpty() && getSize() < num){
    for(int i = 0; i < getSize(); i++){
      toMove.push_back(takeCard());
    }
    hand += toMove;
    return true;
  }
  return false;
}

void Draw::shuffle(vector<int> arr){
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
      shuffled.push_back(cards[*it]);
      //move the chosen card to the back, and decrement last so that
      //the chosen card can't be re-chosen
      swap(cards[*it], cards[last-1]);
      last--;
    }
  }
  else{
    srand(time(NULL));
    while(last--){
      int num = rand() % last;
      shuffled.push_back(cards[num]);
      swap(cards[num],cards[last-1]);
    }
  }
  //replace the old vector with the new shuffled one
  cards = shuffled;
}

void Draw::swap(int& a, int& b){
  int temp = b;
  b = a; 
  a = temp;
}
