#include "Deck.h"
#include <vector>

class Hand: public Deck {
 public:
  Hand();
  int takeCard(int index);
  bool move(Deck& d, int index);
};
