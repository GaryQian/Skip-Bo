/*Names: Kathleen Kusworo, Gary Qian, Sarah Sukardi, Matthew Tan
  Course: Intermediate Programming (AS.600.120)
  Date: 5/01/2015 (First Deadline), 5/08/2015 (Final Deadline)
  Assignment: Final Project-- Skip-Bo
  JHEDs: kkuswor1, gqian1, ssukard1, mtan13
  Email: (JHED)@jhu.edu
*/

#include "Player.h"
#include "Deck.h"
#include "Move.h"
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

    //Creates all of the explicit parameters necessary to create a human player
    Draw* draw = new Draw();
    vector<int> arrange;
    for(int i = 161; i >= 0; i--) {
      arrange.push_back(i);
    }
    draw->shuffle(arrange);
    
    Stock stock;
    draw->move(stock, 30);

    vector<Build*> build;
    //Constructs two HumanPlayers
    HumanPlayer* p1 = new HumanPlayer("Player_1", draw, &build, stock);
    HumanPlayer* p2 = new HumanPlayer("Player_2", draw, &build, stock);

    //Tests constructor VIA accessor methods
    assert (p1->getName() == "Player_1");
    assert (p2->getName() == "Player_2");   
    assert (!p1->isAI());
    assert (!p2->isAI());
  }

  static void cardAccessorTests() {
    //Creates all of the explicit parameters necessary to create a human player
    Draw* draw = new Draw();
    vector<int> arrange;
    for(int i = 161; i >= 0; i--) {
      arrange.push_back(i);
    }
    draw->shuffle(arrange);
    
    Stock stock;
    draw->move(stock, 30);

    vector<Build*> build;
    //Constructs two HumanPlayers
    HumanPlayer* p1 = new HumanPlayer("Player_1", draw, &build, stock);
    HumanPlayer* p2 = new HumanPlayer("Player_2", draw, &build, stock);

    //Tests accessor methods
    assert (p1->getStock().getSize() == 30);
    assert (p2->getStock().getSize() == 30);
    assert (!p1->getHand().getSize());
    assert (!p2->getHand().getSize());
    assert (p1->getDiscard().size() == 4);
    assert (p2->getDiscard().size() == 4);
    assert (p1->getStock().getTop() == 6);
    assert (p2->getStock().getTop() == 6);
    assert (!p1->hasWon());
    assert (!p2->hasWon());
  }

  static void hasWonTest() {
    //Creates all of the explicit parameters necessary to create a human player
    Draw* draw = new Draw();
    vector<int> arrange;
    for(int i = 161; i >= 0; i--) {
      arrange.push_back(i);
    }
    draw->shuffle(arrange);
    
    Stock stock;
    draw->move(stock, 30);

    vector<Build*> build;
    //Constructs two HumanPlayers
    HumanPlayer* p1 = new HumanPlayer("Player_1", draw, &build, stock);
    HumanPlayer* p2 = new HumanPlayer("Player_2", draw, &build, stock);

    //Asserts that a player has not won yet
    assert (!p1->hasWon());
    assert (!p2->hasWon());
  }

  //to be implemented
  static void moveTest() {  }
};

class AITest {
public:
  static void constructorTest() {
    //Creates all of the explicit parameters necessary to create an AI
    Draw* draw = new Draw();
    vector<int> arrange;
    for(int i = 161; i >= 0; i--) {
      arrange.push_back(i);
    }
    draw->shuffle(arrange);
    
    Stock stock;
    draw->move(stock, 30);

    vector<Build*> build;
    //Constructs two AI's
    AI* p1 = new AI("AI", draw, &build, stock);
    AI* p2 = new AI("AI", draw, &build, stock);

    //Tests constructor VIA accessor methods
    assert (p1->getName() == "AI");
    assert (p2->getName() == "AI");   
    assert (p1->isAI());
    assert (p2->isAI());
    assert (p1->getStock().getSize() == 30);
    assert (p2->getStock().getSize() == 30);
    assert (!p1->getHand().getSize());
    assert (!p2->getHand().getSize());
    assert (p1->getDiscard().size() == 4);
    assert (p2->getDiscard().size() == 4);
    assert (p1->getStock().getTop() == 6);
    assert (p2->getStock().getTop() == 6);
  }

  static void containsTest() {
    Draw* draw = new Draw();
    vector<int> arrange;
    for(int i = 161; i >= 0; i--) {
      arrange.push_back(i);
    }
    draw->shuffle(arrange);
    
    Stock stock;
    draw->move(stock, 30);

    vector<Build*> build;
    //Constructs two AI's
    AI* p1 = new AI("AI", draw, &build, stock);
    AI* p2 = new AI("AI", draw, &build, stock);

    vector<int> nums;
    for(int i = 0; i < 20; i++) {
      nums.push_back(i);
    }
    assert(p1->contains(nums, 0));
    assert(p2->contains(nums, 0));
    assert(p1->contains(nums, 1));
    assert(p2->contains(nums, 1));
    assert(p1->contains(nums, 10));
    assert(p2->contains(nums, 10));
    assert(!p1->contains(nums, 20));
    assert(!p2->contains(nums, 20));
    assert(!p1->contains(nums, 100));
    assert(!p2->contains(nums, 100));
  } 

  static void findTest() {
    Draw* draw = new Draw();
    vector<int> arrange;
    for(int i = 161; i >= 0; i--) {
      arrange.push_back(i);
    }
    draw->shuffle(arrange);
    
    Stock stock;
    draw->move(stock, 30);

    vector<Build*> build;
    //Constructs two AI's
    AI* p1 = new AI("AI", draw, &build, stock);
    AI* p2 = new AI("AI", draw, &build, stock);

    vector<int> nums;
    for(int i = 0; i < 20; i++) {
      nums.push_back(i);
    }
    assert(p1->find(nums, 0) == -1);
    assert(p2->find(nums, 0) == -1);
    assert(p1->find(nums, 1) == 1);
    assert(p2->find(nums, 1) == 1);
    assert(p1->find(nums, 10) == 10);
    assert(p2->find(nums, 10) == 10);
    assert(p1->find(nums, 20) == -1);
    assert(p2->find(nums, 20) == -1);
    assert(p1->find(nums, 100) == -1);
    assert(p2->find(nums, 100) == -1);
  }

  static void convertTest() {
    Draw* draw = new Draw();
    vector<int> arrange;
    for(int i = 161; i >= 0; i--) {
      arrange.push_back(i);
    }
    draw->shuffle(arrange);
    
    Stock stock;
    draw->move(stock, 30);

    vector<Build*> build;
    //Constructs an AI
    AI* p1 = new AI("AI", draw, &build, stock);

    assert(p1->convert(3) == "3");
    assert(p1->convert(10) == "10");
    assert(p1->convert(-1) == " ");
  }
};

int main(void) {
  cout << "Running Player tests..." << endl;

  cout << "Running HumanPlayer tests..." << endl;
  HumanPlayerTest::constructorTest();
  HumanPlayerTest::cardAccessorTests();
  HumanPlayerTest::hasWonTest();
  cout << "Passed HumanPlayer tests." << endl;

  cout << "Running AI tests..." << endl;
  AITest::constructorTest();
  AITest::containsTest();
  AITest::findTest();
  AITest::convertTest();
  cout << "Passed AI tests." << endl;

  cout << "Passed all Player tests." << endl;
  return 0;
}
