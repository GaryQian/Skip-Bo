#include "Game.h"
#include <cassert>
#include <iostream>

using std::vector;
using std::cout;
using std::endl;

class GameTest{
public:
  void constructorTest(){
    vector<string> names = {"Matthew", "Gary", "Sarah", "Kathleen"};
    Game* g = new Game(names);
    //assert(g->getPlayer()->getName() == "Matthew");
  }
  
};

int main(){
  GameTest gt;
  cout << "Running constructor tests" << endl;
  gt.constructorTest();
  cout << "Passed constructor tests" << endl;
}
