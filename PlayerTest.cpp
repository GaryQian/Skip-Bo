#include "Player.h"
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

//These tests will be performed on HumanPlayers and AI's, as player is an ABSTRACT CLASS
class HumanPlayerTest {
public:
  static void constructorTest() {

    Draw* draw = new Draw();
    vector<int> arrange;
    for(int i = 161; i >= 0; i--) {
      arrange.push_back(i);
    }
    draw->shuffle(arrange);
    
    Stock stock;
    draw->move(stock, 30);

    Build* build;

    //    HumanPlayer* h1 = new HumanPlayer("Gary", draw, &build, stock);
    
  }

  static void getMoveTest() {

  }

  static void hasWonTest() {
    
  }
  
  static void accessorTest() {
    
  }
};

class AITest {
public:
  static void constructorTest() {
  }

  static void getMoveTest() {
  }

  static void containsTest() {
  } 

  static void findTest() {
  }

  static void convertTest() {
  }
};

int main(void) {
  cout << "Running Player tests..." << endl;

  cout << "Running HumanPlayer tests..." << endl;
  HumanPlayerTest::constructorTest();
  HumanPlayerTest::getMoveTest();
  HumanPlayerTest::hasWonTest();
  HumanPlayerTest::accessorTest();
  cout << "Passed HumanPlayer tests." << endl;

  cout << "Running AI tests..." << endl;
  AITest::constructorTest();
  AITest::getMoveTest();
  AITest::containsTest();
  AITest::findTest();
  AITest::convertTest();
  cout << "Passed AI tests." << endl;

  cout << "Passed Player tests." << endl;
  return 0;
}
