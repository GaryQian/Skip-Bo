#include "Deck.h"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <cassert>

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::ostringstream;

class DrawTest {
public:
  static void constructorTest(){
    Draw d = Draw();
    assert(d.getSize() == 162);
    assert(d.getTop() == 0);
  }
};

int main(void){
  cout << "Running Draw tests..." << endl;
  DrawTest::constructorTest();
  cout << "Passed Draw tests." << endl;
}
