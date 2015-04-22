#include "SkipBoFuncs.h"
#include <stdlib.h>
#include <time.h>

using std::vector;

//Method to create a deck
vector<int> createDeck(){
  vector<int> deck;
  //Inserts 4 sets of 12 numbers
  for(int i = 0; i < 4; i++){
    for(int j = 1; j < 13; j++){
      deck.push_back(j);
    }
  }
  //Inserts "skip-bo" cards
  for(int i = 0; i < 18; i++){
    deck.push_back(0);
  }
  return deck;
}

void shuffle(vector<int> &deck) {
  //Seeds the pseudorandom number generator 
  srand(time(NULL));
  //Stores the vector of shuffled cards
  vector<int> shuffled;
  int num;
  int size = deck.size();

  //Inserts randomly shuffled cards
  while(size--){
    num = rand() % size;
    shuffled.push_back(deck[num]);
    swap(deck[num], deck[size-1]);
  }
  deck = shuffled;
}

//Swap function
void swap(int &a, int &b) {
  int temp;
  temp = a;
  a = b;
  b = temp;
}

