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
  
  static void opsTest() {
    Draw d = Draw();
    vector<int> list;

    for(int i = 0; i < 12; i++){
      list.push_back(i);
    }

    d += list;

    //assert that the topmost cards are now elements of list
    //last element of list should be the topmost card
    for(int i = 0; i < 12; i++){
      assert(d.takeCard() == 12 - i - 1);
    }

    ostringstream oss;
    try {
      d += 13;
    }
    catch (std::invalid_argument & e) {
      oss << e.what(); 
    }

    assert(oss.str() == "Invalid card value.\n");
    
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
      oss << e.what();
    }

    assert(oss.str() == "Deck is empty.\n");
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
    catch(std::invalid_argument & e){
      oss << e.what();
    }

    //assert exception is caught and clear buffer
    assert(oss.str() == "Shouldn't draw more than five cards!\n");
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
      oss << e.what();
    }

    //assert exception is caught
    assert(oss.str() == "Shouldn't draw more than five cards!\n");
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
    ostringstream oss;
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
    b.move(d,d.getSize());

    //assert that only 12k cards are taken, so 1 card is left in Build
    assert(b.getSize() == 1);

    //assert that the Draw pile now has 144 additional cards (will not
    //happen in the real game - only for testing purposes)
    assert(d.getSize() == 162 + 144);    

    //assert that the topmost card in the Draw pile is still the
    //topmost card from before the move was made
    assert(d.getTop() == 0);

    //now assert that the topmost 162 cards are the cards from the
    //original Draw pile, in the original order (to make sure the leftover 
    //cards are not shuffled)
    for(int i = 0; i < 18; i++){
      assert(d.takeCard() == 0);
    }

    for(int i = 0; i < 144; i++){
      assert(d.takeCard() == 12 - i % 12);
    }
  
    //try moving from Build to Draw - should fail because there is only
    //one card left in Build now
    //try {
    b.move(d,1);
    assert(b.getSize() == 1);
    assert(d.getSize() == 144);
      //}
      //catch(std::logic_error & e){
      //oss << e.what();
      //}

    //assert exception is caught
    //assert(oss.str() == "Build pile doesn't have a completed set yet.\n");
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
    vector<int> value = {5, 0, 3, 2, 4};
    int index;

    //add the values to hand
    hand += value;
    
    //assert that hand successfully moves cards to build correctly
    hand.move(build, index = 1);
    assert(hand.getSize() == 4);
    assert(build.getSize() == 1);
    assert(build.getTop() == 0);
    
    //try moving cards from hand to discard
    try {
      //assert that the cards are moved correctly
      hand.move(discard, index = 3);
      assert(hand.getSize() == 3);
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

  static void opsTest() {
    Stock s = Stock();
    vector<int> list;
    ostringstream oss;

    for(int i = 1; i < 13; i++){
      list.push_back(i);
    }

    int num = 1;
    try {
      s += list; num++;
      s += list; num++;
      s += list; num++; //this num++ should not be executed
    }
    catch (std::invalid_argument & e){
      oss << "Failed at num = " << num;
    }
    assert(oss.str() == "Failed at num = 3");
    oss.str("");
    oss.clear();

    //assert Stock pile has 24 cards now
    assert(s.getSize() == 24);

    try {
      s += 13;
    }
    catch (std::invalid_argument & e){
      oss << e.what();
    }

    //assert exception is caught
    assert(oss.str() == "Invalid card value.\n");
    oss.str("");
    oss.clear();

    vector<int> list2 = {5, 3, 2, 1, 0, 1};

    try{
      s += list2;
    } catch(std::invalid_argument & e){
      assert(false); //should not be executed
    }

    assert(s.getSize() == 30);

    try {
      s += 1;
    }catch(std::logic_error & e){
      oss << e.what();
    }

    assert(oss.str() == "Can't have more than 30 cards in Stock pile!\n");
  }

  static void moveTest(){
    ostringstream oss;
    Stock stock = Stock();
    Draw draw = Draw();

    int size;
    try {
      draw.move(stock, size = 26);
      assert(stock.getSize() == 26);
      
      draw.move(stock, size = 5);
    } catch(std::logic_error & e){
      oss << "Failure while trying to take " << size << " cards!";
    }
    assert(oss.str() == "Failure while trying to take 5 cards!");    
    oss.str("");
    oss.clear();
  
    Build build = Build();
    stock += 3;
    try {
      stock.move(build);
      assert(false);
    }
    catch(std::exception & e){
      oss << e.what();
    }
    assert(oss.str() == "Can't add card - not in sequence!\n");
    
  }
};

class DiscardTest {
public:
  static void constructorTest() {
    ostringstream oss;
    Discard discard = Discard();
    assert(discard.isEmpty());
    assert(!discard.getSize());

    try {
      discard.takeCard();
    }
    catch(std::logic_error & e){
      oss << e.what();
    }
    assert(oss.str() == "Deck is empty.\n");
  }

  static void opsTest() {
    Discard discard = Discard();
    vector<int> list(5,2);
    ostringstream oss;

    try {
      discard += 3;
      discard += 5;
      discard += list;
      discard += 13;
      assert(false);
    }
    catch(std::invalid_argument & e){
      oss << e.what();
    }
    assert(oss.str() == "Invalid card value.\n");
    assert(discard.getSize() == 7);
  }

  static void takeCardTest(){
    Discard discard = Discard();
    vector<int> list(5,2);
    ostringstream oss;

    discard += 3;
    discard += 5;
    discard += list;

    for(int i = 0; i < 5; i++){
      assert(discard.takeCard() == 2);
    }

    assert(discard.takeCard() == 5);
    assert(discard.takeCard() == 3);
    assert(discard.isEmpty());
    try {
      discard.takeCard();
    }
    catch(std::logic_error & e){
      oss << e.what();
    }
    assert(oss.str() == "Deck is empty.\n");
  }  

  static void moveTest() {
    Discard discard = Discard();
    Build* bPile = new Build[4];
    vector<int> list(4,1);
    ostringstream oss;

    //add list to discard pile
    discard += list;
    
    //try adding duplicate-valued cards to the same
    //build pile, should catch exception
    try {
      discard.move(bPile[0]);
      discard.move(bPile[0]);
    }
    catch(std::logic_error & e){
      oss << e.what();
    }

    //assert discard pile is decreased by 1
    //and the first build pile now has a card
    assert(discard.getSize() == 3);
    assert(bPile[0].getSize() == 1);

    //assert the right exception is caught and clear buffer
    assert(oss.str() == "Can't add card - not in sequence!\n");
    oss.str("");
    oss.clear();

    //now add the remaining cards in discard pile to each of the other
    //build piles
    for(int i = 1; i < 4; i++){
      discard.move(bPile[i]);
    }
    
    //assert discard pile is now empty
    assert(discard.isEmpty());

    //assert all build piles now have size 1
    for(int i = 0; i < 4; i++){
      assert(bPile[i].getSize() == 1);
    }

    //try moving again from an empty Discard pile, should throw
    //exception before assert(false)
    try {
      discard.move(bPile[0]);
      assert(false);
    }
    catch(std::logic_error & e){
      oss << e.what();
    }

    //assert the right exception is caught
    assert(oss.str() == "Deck is empty.\n");
  }
};

int main(void){
  cout << "Running Draw tests..." << endl;
  DrawTest::constructorTest();
  DrawTest::opsTest();
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
  HandTest::constructorTest();
  HandTest::takeCardTest();
  HandTest::moveTest();
  cout << "Passed Hand tests." << endl;

  cout << "Running Stock tests..." << endl;
  StockTest::constructorTest();
  StockTest::opsTest();
  StockTest::moveTest();
  cout << "Passed Stock tests." << endl;

  cout << "Running Discard tests..." << endl;
  DiscardTest::constructorTest();
  DiscardTest::opsTest();
  DiscardTest::takeCardTest();
  DiscardTest::moveTest();
  cout << "Passed Discard tests." << endl;

}

