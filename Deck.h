#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>

#ifndef DECK_H
#define DECK_H

class Deck {
 protected:  
  std::vector<int> cards; //the vector of integers that represent cards  

 public: 
  /*
   * Returns the number of cards in deck
   */
  int getSize() const;	

  /*
   * Returns the topmost card value without changing the deck
   */
  int getTop() const; 

  /*
   * Removes the topmost card (by deleting the last element of the
   * cards vector, and returns the value of the removed card.
   * Throws a logic error if vector is empty.
   */
  int takeCard() throw (std::logic_error);	

  /*
   * Returns true if vector is empty.
   */
  bool isEmpty() const;
  
  /*
   * Returns the card at the specified index.
   */
  int at(int num);

  /*
   * Moves cards (represented as integers) from a Deck instance's
   * vector to another Deck instance's. Calls the takeCard method.
   */
  void move(Deck& deck) throw (std::logic_error);	

  /*
   * Overloaded operator that pushes an integer to the integer vector
   * of a Deck instance. Throws an exception if we try to add an
   * invalid card number
   */
  virtual void operator +=(int value) throw (std::invalid_argument);	

  /*
   * Overloaded operater that pushes a vector of integers to the
   * existing integer vector of a Deck instance
   */
  virtual void operator +=(std::vector<int> list) throw (std::invalid_argument);

  /*
   * Returns a string that shows the values in a Deck instance's
   * vector of integers
   */
  std::string toString() const; 
};

class Hand: public Deck {
  friend class DrawTest;
  friend class HandTest;
  friend class DisplayTest;
 public:
  Hand();
  
  /*
   * Overloaded takeCard method that takes in an index number and
   * returns the value of the card at that index. Throws an invalid
   * argument if the index is not within the range of Hand's available
   * integer vector, and a logic error if Hand is empty
   */
  int takeCard(int index) throw (std::invalid_argument, std::logic_error);
  
  /*
   * Moves card at index to another Deck's vector of integers.
   */
  void move(Deck& deck, int index) throw (std::invalid_argument, 
					  std::logic_error);

  void operator += (int value)  throw (std::invalid_argument);

  void operator += (std::vector<int> list) throw (std::invalid_argument);

};


class Stock: public Deck {
 public:
  Stock();
  void move(Deck& deck);
  void operator += (int value) throw (std::invalid_argument);
  void operator += (std::vector<int> list) throw (std::invalid_argument);
};

class Draw: public Deck {
  friend class DrawTest;
  friend class DisplayTest;
 public: 

  /*
   * Constructor that creates Draw pile of 162 cards, containing 18
   * Skip-Bo wild cards and 144 regular cards with values 1 to 12
   */
  Draw();

  /*
   * Moves num of cards from Draw pile to Hand. Throws logic error if
   * Draw pile is empty
   */
  void move(Deck& deck, int num) throw (std::invalid_argument);

  //  void move(Stock& stock, int num) throw (std::invalid_argument);

  /*
   * Shuffles the Draw pile based on the arrangement vector that is
   * passed in as an argument/parameter. If the input arrangement
   * vector is empty, then a randomized arrangement will be used.
   */
  void shuffle(std::vector<int> arr = std::vector<int>());

  /*
   * Swaps two elements in a vector of integers
   */
  void swap(int& a, int& b);

  /*
   * Clears contents of draw pile
   */
  void clear();
};

class Build: public Deck {
  friend class BuildTest;
 public:
  Build();

  /*
   * Moves cards from Build pile to Draw pile - used when the Draw
   * pile is empty and the Build pile has a number of completed 1-12
   * sets.
   */
  void move(Draw& draw, int num) throw (std::logic_error);

  /*
   * Overloaded operator that adds cards to the Build pile. Throws an
   * exception if the cards added are not in sequence, or are not
   * Skip-Bo wild cards.
   */
  void operator +=(int value) throw (std::invalid_argument);	
};

class Discard: public Deck { 
  friend class DisplayTest;
public:
  Discard();
  void move(Build& build);
}; 

/*
 * Overloaded << operator for Deck instances
 */
std::ostream& operator << (std::ostream& os, const Deck& d);

#endif
