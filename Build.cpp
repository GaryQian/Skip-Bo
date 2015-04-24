#include "Deck.h"
#include <vector>
#include <algorithm>

using std::vector;
using std::reverse;

Build::Build(){
  cards = vector<int>();
}

bool Build::move(Draw& draw){  
  if(getSize() > 12){
    //reverse the order of the cards, so the bottom cards are now the
    //last elements in the vector
    reverse(cards.begin(), cards.end());
    int max = (getSize()/12) * 12;
    vector<int> toMove;

    //take 12k cards from the Build pile
    for(int i = 0; i < max; i++){
      toMove.push_back(takeCard());
    }    

    //add the cards to the draw pile and shuffle them
    draw += toMove;
    draw.shuffle();

    return true;
  }
  return false;
}
