/*Names: Kathleen Kusworo, Gary Qian, Sarah Sukardi, Matthew Tan
  Course: Intermediate Programming (AS.600.120)
  Date: 5/01/2015 (First Deadline), 5/08/2015 (Final Deadline)
  Assignment: Final Project-- Skip-Bo
  JHEDs: kkuswor1, gqian1, ssukard1, mtan13
  Email: (JHED)@jhu.edu
*/

#include "Game.h"
#include <cassert>
#include <iostream>

using std::vector;
using std::cout;
using std::endl;
using std::invalid_argument;

class GameTest{

  Game* g;
  Game* g1;
  Game* g3;

public:
  ~GameTest(){
    delete g;
    delete g1;
    delete g3;
  }
  
  void clear(vector<Move*> vec){
    for(unsigned long i = 0; i < vec.size(); i++){
      delete vec[i];
    }
  }
  
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
    assert(!g->build.at(0)->getSize());
    assert(!g->build.at(1)->getSize());
    assert(!g->build.at(2)->getSize());
    assert(!g->build.at(3)->getSize());

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
    assert(g->draw->getSize() == 42);
    assert(g->draw->getTop() == 1);

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
    
    //when number of players becomes 5
    names.push_back("Adam");
    g1 = new Game(names, arrange);

    assert(g1->players.size() == 5);
    assert(g1->players.at(0)->getName() == "Matthew");
    assert(g1->players.at(1)->getName() == "AI Gary");
    assert(g1->players.at(2)->getName() == "Sarah");
    assert(g1->players.at(3)->getName() == "Kathleen");
    assert(g1->players.at(4)->getName() == "Adam");

    //checking that last player is not AI
    assert(!g1->players.at(4)->isAI());

    //making sure each player has 20 cards in stock
    assert(g1->players.at(0)->getStock().getSize() == 20);
    assert(g1->players.at(1)->getStock().getSize() == 20);
    assert(g1->players.at(2)->getStock().getSize() == 20);
    assert(g1->players.at(3)->getStock().getSize() == 20);

    //since cards are shuffled backwards, they are arranged in the order
    //1 2 3 4 5 6 7 8 9 10 11 12 1 2 3 4 5 6 7 8
    //9 10 11 12 1 2 3 4 5 6 7 8 9 10 11 12 1 2 3 4 
    //...12 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
    //but each player takes 20 at a time
    assert(g1->players.at(0)->getStock().getTop() == 8);
    assert(g1->players.at(1)->getStock().getTop() == 4);
    assert(g1->players.at(2)->getStock().getTop() == 12);
    assert(g1->players.at(3)->getStock().getTop() == 8);
    assert(g1->players.at(4)->getStock().getTop() == 4);
    assert(g1->draw->getSize() == 62);
    assert(g1->draw->getTop() == 5);

    //empty constructor for game
    Game* g2 = new Game();
    //most variables are NULL or empty or 0
    assert(!g2->players.size());
    assert(!g2->move.size());
    assert(!g2->build.size());
    assert(!g2->turn);
    //but default draw constructor is still called so draw contains 162 cards
    assert(g2->draw->getSize() == 162);
    //draw is not shuffled though
    assert(g2->draw->toString().substr(0, 20) == "1 2 3 4 5 6 7 8 9 10");

    delete g2;
  }

  void ProcessTest(){
    g->nextTurn();
    g->refill();
    //player one starts
    assert(g->turn == 1);
    assert(g->getPlayer()->getName() == "Matthew");
    assert(g->getPlayer()->getHand().getSize() == 5);
    assert(g->getPlayer()->getHand().toString() == "1 2 3 4 5 ");
    assert(g->draw->getSize() == 37);
    assert(g->draw->getTop() == 6);
    
    try {g->process("a");}
    catch (invalid_argument &e) {assert(string(e.what()) == "Invalid input length\n");}
    
    try {g->process("fa bcd");}
    catch (invalid_argument &e) {assert(string(e.what()) == "Unknown card source\nNote: possible sources are (h = hand, s = stock, d = deck)\n");}
				  
    try {g->process("d5 b4");}
    catch (invalid_argument &e) {assert(string(e.what()) == "Invalid discard pile index\n");}
 
    try {g->process("d0 b4");}
    catch (invalid_argument &e) {assert(string(e.what()) == "Invalid discard pile index\n");}

    try {g->process("da b4");}
    catch (invalid_argument &e) {assert(string(e.what()) == "Invalid discard pile index\n");}

    try {g->process("s1 b4");}
    catch (invalid_argument &e) {assert(string(e.what()) == "Stock does not take an index\n");}
    
    try {g->process("h b1");}
    catch (invalid_argument &e) {assert(string(e.what()) == "Invalid hand index\n");}
    
    try {g->process("h1b1");}
    catch (invalid_argument &e) {assert(string(e.what()) == "Source and destination must be separated by a single whitespace\n");}

    try {g->process("h1    b1");}
    catch (invalid_argument &e) {assert(string(e.what()) == "Source and destination must be separated by a single whitespace\n");}

    try {g->process("h1 b");}
    catch (invalid_argument &e) {assert(string(e.what()) == "Invalid input length\n");}

    try {g->process("h1 b5");}
    catch (invalid_argument &e) {assert(string(e.what()) == "Invalid index for destination\n");}

    try {g->process("h1 db");}
    catch (invalid_argument &e) {assert(string(e.what()) == "Invalid index for destination\n");}

    try {g->process("h2 ff");}
    catch (invalid_argument &e) {assert(string(e.what()) == "Unknown card destination\nNote: possible destinations are (d = discard, b = build pile)");}

    try {g->process("h4 b1");}
    catch (invalid_argument &e) {assert(string(e.what()) == "Source and destination do not match");}

    g->process("h1 b1");
    
    assert(g->getPlayer()->getHand().getSize() == 4);
    assert(g->getPlayer()->getHand().toString() == "2 3 4 5 ");
    assert(g->build.at(0)->toString() == "1 ");
    assert(g->move.size() == 1);
  }

  void MoveTest(){
    vector<Move*> choices = g->canMove();
    assert(choices.size() == 1);
    assert(choices.at(0)->toString() == "0 2 h b 0 0 ");
    
    g->process("h1 b1");
    
    assert(g->getPlayer()->getHand().getSize() == 3);
    assert(g->getPlayer()->getHand().toString() == "3 4 5 ");
    assert(g->build.at(0)->toString() == "1 2 ");
    
    clear(choices);

    choices = g->canMove();
    assert(choices.size() == 1);
    assert(choices.at(0)->toString() == "0 3 h b 0 0 ");

    g->process("h1 b1");

    assert(g->getPlayer()->getHand().getSize() == 2);
    assert(g->getPlayer()->getHand().toString() == "4 5 ");
    assert(g->build.at(0)->toString() == "1 2 3 ");
    
    clear(choices);

    choices = g->canMove();
    assert(choices.size() == 1);
    assert(choices.at(0)->toString() == "0 4 h b 0 0 ");
    
    g->process("h1 b1");

    assert(g->getPlayer()->getHand().getSize() == 1);
    assert(g->getPlayer()->getHand().toString() == "5 ");
    assert(g->build.at(0)->toString() == "1 2 3 4 ");
    
    clear(choices);

    choices = g->canMove();
    assert(choices.size() == 1);
    assert(choices.at(0)->toString() == "0 5 h b 0 0 ");

    g->process("h1 b1");

    assert(g->getPlayer()->getHand().getSize() == 0);
    g->refill();
    assert(g->getPlayer()->getHand().toString() == "6 7 8 9 10 ");
    assert(g->build.at(0)->toString() == "1 2 3 4 5 ");
    
    clear(choices);
    
    choices = g->canMove();
    assert(choices.size() == 2);
    assert(choices.at(0)->toString() == "0 6 h b 0 0 ");
    assert(choices.at(1)->toString() == "0 6 s b 0 0 ");
    
    g->process("s b1");

    assert(g->build.at(0)->toString() == "1 2 3 4 5 6 ");
    assert(g->getPlayer()->getStock().getTop() == 5);
    assert(g->move.size() == 6);

    g->process("h2 b1");
    g->process("h2 b1");
    g->process("h2 b1");
    g->process("h2 b1");

    assert(g->build.at(0)->toString() == "1 2 3 4 5 6 7 8 9 10 ");
    assert(g->getPlayer()->getHand().toString() == "6 ");
    assert(g->move.size() == 10);

    //end of player 1's turn
    //build pile: 10 0 0 0
    //p1 discard 0 0 0 0
    //p1 hand 6 0 0 0 
    //p1 stock 5
   
    g->nextTurn();
    g->refill();
    //player 2 start
    assert(g->turn == 2);
    assert(g->getPlayer()->getHand().getSize() == 5);
    assert(g->draw->getSize() == 27);
    assert(g->draw->getTop() == 4);

    assert(g->getPlayer()->getHand().toString() == "11 12 1 2 3 ");
    
    g->process("h1 b1");
    g->process("h1 b1");
    g->process("h1 b1");
    g->process("h1 b1");
    try {g->process("h1 d1");}
    catch (int a) {assert(a == 1);}

    assert(g->getPlayer()->getDiscard().at(0)->getTop() == 3);
    assert(g->getPlayer()->getHand().toString() == "");
    assert(g->getPlayer()->getStock().getTop() == 12);
    assert(g->move.size() == 15);

    //end of player 2's turn
    //build 2 0 0 0
    //p2 discard 3 0 0 0
    //p2 hand 
    //p2 stock 12

    //player 3 starts    
    g->nextTurn();
    g->refill();

    assert(g->turn == 3);
    assert(g->getPlayer()->getHand().getSize() == 5);
    assert(g->draw->getSize() == 22);
    assert(g->getPlayer()->getHand().toString() == "4 5 6 7 8 ");
    assert(g->getPlayer()->getStock().getTop() == 6);

    clear(choices);
    
    choices = g->canMove();
    assert(choices.size() == 0);
    
    try {g->process("h2 d2");}
    catch (int a) { assert(a == 1);}
  
    assert(g->getPlayer()->getHand().toString() == "4 6 7 8 ");
    assert(g->getPlayer()->getDiscard().at(1)->getTop() == 5);
    assert(g->move.size() == 16);

    //end of player 3's turn
    //build 2 0 0 0
    //p3 discard 0 5 0 0
    //p3 hand 4 6 7 8
    //p3 stock 6
   
    //start of player 4's turn
    g->nextTurn();
    g->refill();

    assert(g->turn == 4);
    assert(g->getPlayer()->getHand().getSize() == 5);
    assert(g->draw->getSize() == 17);
    assert(g->getPlayer()->getHand().toString() == "9 10 11 12 0 ");
    assert(g->getPlayer()->getStock().getTop() == 12);
    
    clear(choices);
    
    choices = g->canMove();
    assert(choices.size() == 4);
    
    g->process("h5 b1");
    assert(g->build.at(0)->getSize()%12 == 3);
    assert(g->getPlayer()->getHand().toString() == "9 10 11 12 ");
    assert(g->move.size() == 17);
    
    clear(choices);
  }
  
  void saveLoadTest(){
    g->save_game("test_save_0");
    g3 = new Game();
    g3->load_game("test_save_0");

    //this is the looping of loading and saving 300 times
    /*
    for(int i = 0; i < 300; i++){
      std::ostringstream oss;
      oss << "test_save_" << i;
      g -> save_game(oss.str());
      g3 -> load_game(oss.str());
      }*/
   
    
    for(int i = 0; i < 4; i++){
      assert(g3->build.at(i)->toString() == g->build.at(i)->toString());
    }

    assert(g3->draw->toString() == g->draw->toString());

    for(unsigned long i = 0; i < g3->players.size(); i++){
      assert(g3->players.at(i)->getName() == g->players.at(i)->getName());
    
      assert(g3->players.at(i)->getStock().toString() == g->players.at(i)->getStock().toString());
      
      assert(g3->players.at(i)->getHand().toString() == g->players.at(i)->getHand().toString());
      
      for(int j = 0; j < 4; j++){
	assert(g3->players.at(i)->getDiscard().at(j)->toString() == g->players.at(i)->getDiscard().at(j)->toString());
      }
    }
    
    for(unsigned long i = 0; i < g3->move.size(); i++){
      assert(g3->move.at(i)->toString() == g->move.at(i)->toString());
    }
    delete g3;
    
  }

  void undoTest(){
    //assume g is the first saved game state
    g -> save_game("move_1");

    g3 = new Game(); 
    g3 -> load_game("move_1");

    *(g3 -> build.at(0)) += 4;
    *(g3 -> draw) += 4;

    cout << *(g3 -> build.at(0)) << endl;
    cout << *(g -> draw) << endl;

    g3 -> undo(1);

    for(int i = 0; i < 4; i++){ 
      cout << i << endl;
      cout << *(g3 -> build.at(i)) << endl;
      cout << *(g -> build.at(i)) << endl;
      assert(g3->build.at(i)->toString() == g->build.at(i)->toString());
    }

    assert(g3 -> draw -> toString() == g -> draw -> toString());
    
    }
};

/*int main(){
  GameTest gt;
  cout << "Running constructor tests" << endl;
  gt.constructorTest();
  cout << "Passed constructor tests" << endl;
  cout << "Running process method tests" << endl;
  gt.ProcessTest();
  cout << "Passed process method tests" << endl;
  cout << "Running move method tests" << endl;
  gt.MoveTest();
  cout << "Passed move method tests" << endl;
  cout << "Running save/load method tests" << endl;
  gt.saveLoadTest();
  cout << "Passed save/load method tests" << endl;
  return 0;
}
*/
