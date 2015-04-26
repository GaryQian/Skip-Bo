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
    ostringstream oss;
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
  
    //since draw pile is now empty, try calling takeCard
    //method should throw an exception and assert(false) will not be executed
    try { 
      d.takeCard();
      assert(false);
    }
    catch(std::logic_error & e){
      oss << "Failure.";
    }
    assert(oss.str() == "Failure.");
  }

  static void shuffleTest(){
    Draw d = Draw();
    vector<int> arr;
    for(int i = 161; i >= 0; i--){
      arr.push_back(i);
    }

    //shuffle based on arrangement (should reverse the original draw pile)
    d.shuffle(arr);

    //assert that the cards are now in reversed arrangement
    vector<int>::const_iterator it;    
    for(it = (d.cards).begin(); it < (d.cards).begin() + 18; it++){
      assert(*it == 0);
    }
    int i;
    for(it = (d.cards).begin() + 18, i = 0; it < (d.cards).end(); it++, i++){
      assert(*it == 12 - i % 12);
    }

    //now use the randomized shuffle
    d.shuffle();

    //assert the size is still the same
    assert(d.getSize() == 162);
  }

  static void moveTest(){
    //declare new empty Hand and a Draw pile
    Hand h = Hand();
    Draw d = Draw();
    ostringstream oss;

    //try drawing more than 5 cards to Hand
    //exception should be caught before assert(false)
    try {
      d.move(h,6);
      assert(false);
    }
    catch(std::logic_error & e){
      oss << "Can't move!";
    }

    //assert exception is caught and clear buffer
    assert(oss.str() == "Can't move!");
    oss.str("");
    oss.clear();

    //move 5 cards from Draw pile to Hand
    d.move(h,5);
    
    //assert Hand now has 5 cards
    assert(h.getSize() == 5);
    
    //since we are taking from the topmost, unshuffled draw pile, the
    //five cards taken should be wild Skip-Bo Cards
    vector<int>::const_iterator it;
    for(it = (h.cards).begin(); it < (h.cards).end(); it++){
      assert(*it == 0);
    }

    //assert that the size of the Draw pile is decreased by 5
    assert(d.getSize() == 162 - 5);

    //assert that the rest of the draw pile is of the values expected
    int i;
    for(it = (d.cards).begin(), i=0; it < (d.cards).begin() + 144; it++, i++){
      assert(*it == i % 12 + 1);
    }
    for(it = (d.cards).begin() + 144; it < (d.cards).end(); it++){
      assert(*it == 0);
    }
    

    //try drawing more cards to the full Hand
    try {
      d.move(h,1);
      assert(false);
    }
    catch (std::logic_error & e){
      oss << "Hand is full.";
    }

    //assert exception is caught
    assert(oss.str() == "Hand is full.");
  }
};

class BuildTest {
public:
  static void constructorTest(){
    Build b = Build();
    assert(b.getSize() == 0); 
  }

  static void opsTest(){
    Build b = Build();
    ostringstream oss;
    int num;

    //try adding card of value 2 to an empty Build pile
    //should throw an exception before assert(false)
    try {
      num = 2;
      b += num;
      assert(false);
    }
    catch (std::logic_error & e){
      oss << "Failed when trying to add card of value " << num;
    }

    //assert that exception is caught correctly
    assert(oss.str() == "Failed when trying to add card of value 2");

    //try adding 1 to 12, then 13
    try {
      num = 1;
      b += num;
      assert(b.getTop() == 1);
      
      for(num = 2; num < 13; num++){
	b += num;
      }

      //add 13 to Build
      b += num;
    }
    catch (std::invalid_argument & e){
      oss << " and " << num;
    }

    //assert that exception is caught correctly
    assert(oss.str() == "Failed when trying to add card of value 2 and 13");

    //assert that now the topmost card is of value 12
    assert(b.getTop() == 12);

    //try adding wild Skip-Bo cards - should not throw an exception
    try {
      for(int i = 0; i < 30; i++){
	b += 0;      
      }
    }
    catch(std::invalid_argument & e){
      assert(false); //should not be executed
    }    
  }
  
  static void moveTest(){
    Build b = Build();
    Draw d = Draw();

    int i;
    //add 145 cards, numbered 1-12 at every iteration 
    try {
      for(i = 0; i < 145; i++){
	b += i % 12 + 1;
      }
    } catch (std::invalid_argument){
      assert(false); //shouldn't be executed
    }

    //assert that Build has 145 cards now
    assert(b.getSize() == 145);

    //move Build cards to Draw
    b.move(d);

    //assert that only 12k cards are taken, so 1 card is left in Build
    assert(b.getSize() == 1);

    //assert that the Draw pile now has 144 additional cards (will not
    //happen in the real game - only for testing purposes)
    assert(d.getSize() == 162 + 144);    

    //assert that the topmost card in the Draw pile is still the
    //topmost card from before the move was made
    assert(d.getTop() == 0);

    //now assert that the topmost 162 cards are the cards from the
    //original Draw pile
    for(int i = 0; i < 18; i++){
      assert(d.takeCard() == 0);
    }

    for(int i = 0; i < 144; i++){
      assert(d.takeCard() == 12 - i % 12);
    }
  }
};

class HandTest {
public:
  static void constructorTest(){
    Hand h = Hand();
    assert(h.getSize() == 0);
  }

  static void takeCardTest(){
    ostringstream oss;
    
    //add 5 cards to the hand
    Hand h = Hand();

    //try taking a card from an empty Hand., should catch exception
    //before assert(false)
    try {
      h.takeCard(0);
      assert(false);
    }
    catch(std::logic_error & e){
      oss << "Hand is empty.\n";
    }

    //assert that exception is caught, then empty ostringstream buffer
    assert(oss.str() == "Hand is empty.\n");
    oss.str("");
    oss.clear();

    vector<int> value = {5, 3, 4, 2, 1};
    h += value;

    int index = 0;
    try {
      //check that takeCard takes the right card
      assert(h.takeCard(index) == 5);
      assert(h.takeCard(index) == 3);
      assert(h.takeCard(index = 2) == 1);

      //try inputting an invalid index, and make sure the exception is
      //caught if exception is caught, then assert(false) will not be
      //executed and the program will not abort
      h.takeCard(index = 5);
      assert(false);
    }
    catch(std::invalid_argument & e){
      oss << "Failed after trying to take card at index " << index << "!";
    }

    //assert that the code inside the catch block is caught
    assert(oss.str() == "Failed after trying to take card at index 5!");
  }  

  static void moveTest(){
    //initialize all variables
    ostringstream oss;
    Discard discard = Discard();
    Build build = Build();
    Hand hand = Hand();
    vector<int> value = {5, 0, 3, 2, 4, 5};
    int index;

    //add the values to hand
    hand += value;
    
    //assert that hand successfully moves cards to build correctly
    hand.move(build, index = 1);
    assert(hand.getSize() == 5);
    assert(build.getSize() == 1);
    assert(build.getTop() == 0);
    
    //try moving cards from hand to discard
    try {
      //assert that the cards are moved correctly
      hand.move(discard, index = 3);
      assert(hand.getSize() == 4);
      assert(discard.getSize() == 1);

      //assert that an exception is thrown, so that assert(false) will
      //not be executed
      hand.move(discard, index = 6);
      assert(false);
    }
    //should catch invalid_argument, not logic_error
    catch(std::invalid_argument & e){
      oss << "Failed after trying to take a card of index " << index << "!"; 
    }
    catch(std::logic_error & e){
      oss << "I shouldn't be thrown!";
    }

    //assert that the code inside the catch block is executed
    assert(oss.str() == "Failed after trying to take a card of index 6!");
  }
};

class StockTest {
public:
  static void constructorTest() {
    Stock s = Stock();
    assert(s.getSize() == 0);
    assert(s.isEmpty());
  }  
};

int main(void){
  cout << "Running Draw tests..." << endl;
  DrawTest::constructorTest();
  DrawTest::takeCardTest();
  DrawTest::shuffleTest();
  DrawTest::moveTest();
  cout << "Passed Draw tests." << endl;

  cout << "Running Build tests..." << endl;
  BuildTest::constructorTest();
  BuildTest::opsTest();
  BuildTest::moveTest();
  cout << "Passed Build tests." << endl;

  cout << "Running Hand tests..." << endl;
  HandTest::takeCardTest();
  HandTest::moveTest();
  cout << "Passed Hand tests." << endl;

  cout << "Running Stock tests..." << endl;
  StockTest::constructorTest();
  cout << "Passed Stock tests." << endl;
}
