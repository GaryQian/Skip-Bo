#include <string>
#include <vector>

class player{
  std::string name;
  std::vector<int> hand;
  std::vector<int> stock;
  std::vector<int> draw;
  std::vector<int> discard;


  player(std::string name); //constructor
};
