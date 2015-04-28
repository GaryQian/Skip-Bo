#include "Game.h"
#include <cassert>
#include <iostream>

using std::vector;
using std::cout;
using std::endl;

class GameTest{
public:
  void constructorTest(){
    vector<int> arrange;
    for(int i = 161; i >= 0; i--){
      arrange.push_back(i);
    }
    vector<string> names = {"Matthew", "Gary", "Sarah", "Kathleen"};
    Game* g = new Game(names, arrange);
    assert(g->players.size() == 4);
    assert(g->players.at(0)->getName() == "Matthew");
    assert(g->players.at(1)->getName() == "Gary");
    assert(g->players.at(2)->getName() == "Sarah");
    assert(g->players.at(3)->getName() == "Kathleen");

    assert(g->build.size() == 4);
    assert(!g->build.at(0).getSize());
    assert(!g->build.at(1).getSize());
    assert(!g->build.at(2).getSize());
    assert(!g->build.at(3).getSize());

    assert(!g->move.size());

    assert(g->players.at(0)->getStock().getSize() == 30);
    assert(g->players.at(1)->getStock().getSize() == 30);
    assert(g->players.at(2)->getStock().getSize() == 30);
    assert(g->players.at(3)->getStock().getSize() == 30);

    cout << g->draw.toString() << endl;
    cout << g->players.at(0)->getStock().toString() << endl;
    cout << g->players.at(1)->getStock().toString() << endl;
    cout << g->players.at(2)->getStock().toString() << endl;
    cout << g->players.at(3)->getStock().toString() << endl;
    
    
  }
  
};

int main(){
  GameTest gt;
  cout << "Running constructor tests" << endl;
  gt.constructorTest();
  cout << "Passed constructor tests" << endl;
}
