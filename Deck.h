#include <vector>

using std::vector;

class Deck {
 protected:
  vector<int> cards;	
  int size;

 public: 
  Deck();
  int getSize();	
  int getTop(); //do we need this? take() basically does the same thing	
  int takeCard();	
  bool isEmpty();
  bool move(Deck b);	
  bool move(Deck b, int num);	
  void operator +=(int value);	
  void operator +=(vector<int> list);
  void print(); 
};
