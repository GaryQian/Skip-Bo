#include "Build.h"
#include <vector>
#include <algorithm>

using std::vector;
using std::reverse;

Build::Build(){
  size = 0;
}

bool Build::move(Draw& d){
  if(size > 12){
    //reverse the order of the cards, so the bottom cards are now the
    //last elements in the vector
    reverse(cards.begin(), cards.end());
    int max = (size/12) * 12;
    vector<int> toMove;

    //take 12k cards from the Build pile
    for(int i = 0; i < max; i++){
      toMove.push_back(takeCard());
    }
    //add the cards to the draw pile and shuffle them
    d += toMove;
    d.shuffle();
    return true;
  }
  return false;
}
