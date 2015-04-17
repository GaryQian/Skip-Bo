#include "playerClass.h"
#include "SkipBoFuncs.h"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int main(){
  vector<int> deck = createDeck();
  shuffle(deck);

  int numPlayers;
  cout << "How many players? " << endl;
  cin >> numPlayers;
  
  //player playerList[numPlayers];
  //for(int i = 1; i <= numPlayers; ++i){
  //  cout << "Enter player " << i << "'s name: " << endl;
    
  //}
}
