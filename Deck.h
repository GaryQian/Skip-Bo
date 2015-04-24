#include <vector>
#include <string>
#include <sstream>

class Deck {
 protected:  
  std::vector<int> cards; //the vector of integers that represent cards  

 public: 
  int getSize();	
  int getTop(); 
  virtual int takeCard();	
  bool isEmpty();
  virtual bool move(Deck& d, int num = 1) = 0;	
  //bool move(Deck b, int num);	
  void operator +=(int value);	
  void operator +=(std::vector<int> list);
  std::string toString() const; 
};

class Hand: public Deck {
 public:
  Hand();
  int takeCard(int index);
  bool move(Deck& d, int index);
};

class Draw: public Deck {
  public: 
   Draw();
   bool move(Deck& d, int num);
   void shuffle(std::vector<int> arr = std::vector<int>());
   void swap(int& a, int& b);
};

class Build: public Deck {
 public:
  Build();
  bool move(Deck& d, int num);
};

class Discard: public Deck { 
public:
  Discard();
  bool move(Build& b);
}; 


std::ostream& operator << (std::ostream& os, const Deck& d);
