#include <vector>
#include <string>
#include <sstream>

class Deck {
 protected:  
  std::vector<int> cards; //the vector of integers that represent cards  

 public: 
  Deck();
  int getSize();	
  int getTop(); 
  virtual int takeCard() = 0;	
  bool isEmpty();
  virtual bool move(Deck& d);	
  //bool move(Deck b, int num);	
  void operator +=(int value);	
  void operator +=(std::vector<int> list);
  std::string toString() const; 
};

std::ostream& operator << (std::ostream& os, const Deck& d);
