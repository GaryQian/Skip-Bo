#include "Game.h"
#include <cassert>
#include <iostream>

using std::vector;
using std::cout;
using std::endl;

class GameTest{

  Game* g;

public:
  void constructorTest(){
    vector<int> arrange;

    //this arrangement makes the cards rearrange backwards when shuffle is called
    for(int i = 161; i >= 0; i--){
      arrange.push_back(i);
    }

    //vector of strings to input into game
    vector<string> names = {"Matthew", "AI Gary", "Sarah", "Kathleen"};

    //default game constructor
    g = new Game(names, arrange);

    //checking that the player names where stored in correct order
    assert(g->players.size() == 4);
    assert(g->players.at(0)->getName() == "Matthew");
    assert(g->players.at(1)->getName() == "AI Gary");
    assert(g->players.at(2)->getName() == "Sarah");
    assert(g->players.at(3)->getName() == "Kathleen");

    //checking that second player is AI
    assert(!g->players.at(0)->isAI());
    assert(g->players.at(1)->isAI());
    assert(!g->players.at(2)->isAI());
    assert(!g->players.at(3)->isAI());

    //checking build piles were constructed correctly
    assert(g->build.size() == 4);
    assert(!g->build.at(0).getSize());
    assert(!g->build.at(1).getSize());
    assert(!g->build.at(2).getSize());
    assert(!g->build.at(3).getSize());

    //checking move vector is still empty
    assert(!g->move.size());

    //making sure each player has 30 cards in stock
    assert(g->players.at(0)->getStock().getSize() == 30);
    assert(g->players.at(1)->getStock().getSize() == 30);
    assert(g->players.at(2)->getStock().getSize() == 30);
    assert(g->players.at(3)->getStock().getSize() == 30);

    //since cards are shuffled backwards, they are arranged in the order
    //1 2 3 4 5 6 7 8 9 10 11 12 1 2 3 4 5 6 7 8 9 10 11 12 1 2 3 4 5 6
    //7 8 9 10 11 12 1 2 3 4 5 6 7 8 9 10 11 12 1 2 3 4 5 6 7 8 9 10 11 12
    //...12 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
    //so each player takes thirty at a time
    assert(g->players.at(0)->getStock().getTop() == 6);
    assert(g->players.at(1)->getStock().getTop() == 12);
    assert(g->players.at(2)->getStock().getTop() == 6);
    assert(g->players.at(3)->getStock().getTop() == 12);
    assert(g->draw.getTop() == 1);

    //each player has 0 cards in hand since they only draw during their turn
    assert(!g->players.at(0)->getHand().getSize());
    assert(!g->players.at(1)->getHand().getSize());
    assert(!g->players.at(2)->getHand().getSize());
    assert(!g->players.at(3)->getHand().getSize());

    //making sure each players has 4 discard piles
    assert(g->players.at(0)->getDiscard().size() == 4);
    assert(g->players.at(0)->getDiscard().size() == 4);
    assert(g->players.at(0)->getDiscard().size() == 4);
    assert(g->players.at(0)->getDiscard().size() == 4);
  
    //turn is 0
    assert(!g->turn);
    
    //empty constructor for game
    Game* g2 = new Game();
    //most variables are NULL or empty or 0
    assert(!g2->players.size());
    assert(!g2->move.size());
    assert(!g2->build.size());
    assert(!g2->turn);
    //but default draw constructor is still called so draw contains 162 cards
    assert(g2->draw.getSize() == 162);
    //draw is not shuffled though
    assert(g2->draw.toString().substr(0, 20) == "1 2 3 4 5 6 7 8 9 10");

    delete g2;
  }

  void helperTest(){
    g->nextTurn();
    assert(g->turn == 1);
    assert(g->getPlayer()->getName() == "Matthew");
    assert(g->getPlayer()->getHand().getSize() == 5);
    assert(g->getPlayer()->getHand().toString() == "1 2 3 4 5 ");
  }
  
};

int main(){
  GameTest gt;
  cout << "Running constructor tests" << endl;
  gt.constructorTest();
  cout << "Passed constructor tests" << endl;
  cout << "Running helper method tests" << endl;
  gt.helperTest();
  cout << "Passed helper method tests" << endl;
}
