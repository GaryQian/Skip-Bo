#include "SkipBoFuncs.h"
#include <stdlib.h>
#include <time.h>

using std::vector;

vector<int> createDeck(){
  vector<int> deck;
  for(int i = 0; i < 4; i++){
    for(int j = 1; j < 13; j++){
      deck.push_back(j);
    }
  }
  for(int i = 0; i < 18; i++){
    deck.push_back(0);
  }
  return deck;
}

void shuffle(vector<int> &deck){
  srand(time(NULL));
  vector<int> shuffled;
  int num;
  int size = deck.size();

  while(size--){
    num = rand() % size;
    shuffled.push_back(deck[num]);
    swap(deck[num], deck[size-1]);
  }
  deck = shuffled;
}

void swap(int &a, int &b){
  int temp;
  temp = a;
  a = b;
  b = temp;
}

