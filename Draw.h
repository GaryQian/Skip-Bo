#include "Hand.h"
#include <string>
#include <vector>

class Draw: public Deck {
 public: 
  Draw();
  bool move(Hand& h, int num);
  void shuffle(std::vector<int> arr = std::vector<int>());
  void swap(int& a, int& b);
};
