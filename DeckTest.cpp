#include "Deck.h"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::ostringstream;

void constructorTest(){
  Draw d();

}

int main(void){
  cout << "Running Deck tests..." << endl;
  constructorTest();
  cout << "Passed Deck tests." << endl;
}
