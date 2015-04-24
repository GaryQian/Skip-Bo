#include "Deck.h"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <cassert>
#include <cstdlib>

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::ostringstream;
using std::iterator;

class DrawTest {
public:
  static void constructorTest(){
    //assert that a draw pile of 162 cards is constructed
    //and the topmost card is a Skip-Bo card
    Draw d = Draw();
    assert(d.getSize() == 162);
    assert(d.getTop() == 0);
    
    //assert that the vector cards contains the correct values
    vector<int>::iterator it;
    int i = 0;
    for(it = (d.cards).begin(); it < (d.cards).end() - 18; it++, i++){
      assert(*it == (i % 12) + 1);
    } 

    //assert that the last 18 cards are Skip-Bo cards
    for(it = (d.cards).end() - 18; it < (d.cards).end(); it++){
      assert(*it == 0);
    }
  }

  static void takeCardTest(){
    //construct a draw pile and save the original size
    Draw d = Draw();
    int size = d.getSize();

    //assert that the topmost 18 cards are Skip-Bo cards and assert
    //that the vector of integers is decreasing as cards are taken
    for(int i = 0; i < 18; i++){
      assert(d.takeCard() == 0);
      assert(d.getSize() == size - i - 1);
    }    
    size = d.getSize();
    
    //assert that the leftover cards are 1 to 12, in decreasing order
    //assert that the size is decreasing
    for(int i = 0; i < 144; i++){
      assert(d.takeCard() == 12 - i % 12);
      assert(d.getSize() == size - i - 1);
    }    
    assert(d.getSize() == 0);
  }

  static void shuffleTest(){
    
  }
};

class BuildTest {
public:
  static void constructorTest(){
    Build b = Build();
    assert(b.getSize() == 0);
  }
};

int main(void){
  cout << "Running Draw tests..." << endl;
  DrawTest::constructorTest();
  DrawTest::takeCardTest();
  cout << "Passed Draw tests." << endl;
}
