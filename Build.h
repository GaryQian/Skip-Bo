#include <vector>

using std::vector;

class Build {
	
	static vector<vector<int>> piles;
	
	static vector<bool> full;
	
	Build() {
		piles.push_back(new vector<int>());
		piles.push_back(new vector<int>());
		piles.push_back(new vector<int>());
		piles.push_back(new vector<int>());
	}

};