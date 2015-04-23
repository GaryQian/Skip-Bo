#include "Draw.h"

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

bool Draw::move(Deck& d, int num){
  if(getSize() >= num){

    vector<int> toAdd;
    toAdd.reserve(num);

    //take num cards from this deck
    for(int i = 0; i < num; i++){
      toAdd.push_back(takeCard());
    }
    
    d += toAdd;
    return true;
  }
  return false;
}
