#include <vector>

using std::vector;

class Deck {
	vector<int> cards;
	
	Deck();
	
	int getSize();
	
	int getTop();
	
	int take();
	
	move(Deck b);
	
	move(Deck b, int num);
	
	void operator +=(int value);
	
	void operator +=(vector<int> list);
	
};