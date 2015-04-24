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
  virtual bool move(Deck& deck);	
  void operator +=(int value);	
  void operator +=(std::vector<int> list);
  std::string toString() const; 
};

class Hand: public Deck {
 public:
  Hand();
  int takeCard(int index);
  bool move(Deck& deck, int index);
};

class Draw: public Deck {
  friend class DrawTest;
 public: 
  Draw();
  bool move(Hand& hand,int num);
  void shuffle(std::vector<int> arr = std::vector<int>());
  void swap(int& a, int& b);
};

class Build: public Deck {
 public:
  Build();
  bool move(Draw& draw);
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
//void shuffle(std::vector<int>& v, std::vector<int> arr = std::vector<int>());
//void swap(int& a, int& b);
