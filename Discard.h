#include <vector>

using std::vector;

class Discard {
	vector<vector<int>> piles;
	
	Build() {
		piles.push_back(new vector<int>());
		piles.push_back(new vector<int>());
		piles.push_back(new vector<int>());
		piles.push_back(new vector<int>());
	}
	
};