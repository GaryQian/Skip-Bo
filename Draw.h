#include "Deck.h"
#include <string>
#include <vector>

class Draw: public Deck {
 public: 
  Draw();
  bool move(Deck& d, int num);
};
