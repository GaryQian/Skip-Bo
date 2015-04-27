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

class PlayerTest {
public:
  static void constructorTest() {
    Player* p = new Player("Laura", 
  }
  
  static void moveTest() {

  }

  static void hasWonTest() {

  }

  static void accessorTest() {

  }
};

int main(void) {
  cout << "Running Player tests..." << endl;
  PlayerTest::constructorTest();
  PlayerTest::moveTest();
  PlayerTest::hasWonTest();
  PlayerTest::accessorTest();
  cout << "Passed Player tests." << endl;
  return 0;
}
