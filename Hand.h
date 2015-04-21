#include <vector>

using std::vector;

class Hand: public Deck {
    
    Hand() {
        
    }
	
	int at(int num) {
		return cards.at(num);
		
	}




};