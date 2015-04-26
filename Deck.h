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
  int getSize() const;	
  int getTop() const; 
  int takeCard() throw (std::logic_error);	
  bool isEmpty() const;
  void move(Deck& deck) throw (std::logic_error);	
  void operator +=(int value);	
  void operator +=(std::vector<int> list);
  std::string toString() const; 
};

class Hand: public Deck {
  friend class DrawTest;
  friend class HandTest;
 public:
  Hand();
  int takeCard(int index) throw (std::invalid_argument, std::logic_error);
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
