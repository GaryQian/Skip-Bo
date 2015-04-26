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
   * Moves cards (represented as integers) from a Deck instance's
   * vector to another Deck instance's. Calls the takeCard method.
   */
  void move(Deck& deck) throw (std::logic_error);	

  /*
   * Overloaded operator that pushes an integer to the integer vector
   * of a Deck instance
   */
  void operator +=(int value);	

  /*
   * Overloaded operater that pushes a vector of integers to the
   * existing integer vector of a Deck instance
   */
  void operator +=(std::vector<int> list);

  /*
   * Returns a string that shows the values in a Deck instance's
   * vector of integers
   */
  std::string toString() const; 
};

class Hand: public Deck {
  friend class DrawTest;
  friend class HandTest;
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
};

class Draw: public Deck {
  friend class DrawTest;
 public: 
  Draw();
  void move(Hand& hand, int num) throw (std::logic_error);
  void shuffle(std::vector<int> arr = std::vector<int>());
  void swap(int& a, int& b);
};

class Build: public Deck {
  friend class BuildTest;
 public:
  Build();
  void move(Draw& draw) throw (std::logic_error);
  void operator +=(int value) throw (std::invalid_argument);	
};

class Discard: public Deck { 
public:
  Discard();
  //bool move(Build& build);
}; 

class Stock: public Deck {
 public:
  Stock();
};

std::ostream& operator << (std::ostream& os, const Deck& d);

#endif
