#include <string>
#include <vector>
#include "Hand.h"
#include "Discard.h"
#include "Draw.h"


using std::string;
using std::vector;

class player{
  string name;
  Hand hand;
  vector<int> stock;
  Draw draw;
  Discard discard;


  player(std::string name); //constructor
};
