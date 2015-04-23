#include <vector>
#include <string>
#include <sstream>

class Deck {
 protected:  
  std::vector<int> cards; //the vector of integers that represent cards  
  int size; //the number of cards in the deck

 public: 
  Deck();
  int getSize();	
  int getTop(); 
  int takeCard();	
  bool isEmpty();
  virtual bool move(Deck& d) = 0;	
  //bool move(Deck b, int num);	
  void operator +=(int value);	
  void operator +=(std::vector<int> list);
  std::string toString() const; 
};

std::ostream& operator << (std::ostream& os, const Deck& d);
