#include <vector>

using std::vector;

Deck::Deck();

int Deck::getSize() {
  return cards.size();
}

int Deck::take();

int Deck::getTop() {
  return cards.back();
}

void Deck::move(Deck b);

void Deck::move(Deck b, int num);

void Deck::operator +=(int value);

void Deck::operator +=(vector<int> list);
