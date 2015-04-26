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

void Build::operator +=(int value) throw (std::invalid_argument){
  if((value == 1) && (getTop() != 12) && (getTop() != 0) && 
		     (getTop() != -1)){
    throw std::invalid_argument("Can't add card - not in sequence!\n");
  }
  else if(value != 1 && getTop() != value - 1 && getTop() != 0){
    throw std::invalid_argument("Can't add card - not in sequence!\n");
  }  
  else (Deck::operator +=(value));
}
