#include <fstream>
#include <iostream>

using std::ofstream;
using std::endl;

int main(void){
  ofstream outfile("test_speed.txt");
  
  outfile << "no" << endl;
  outfile << "2" << endl;
  outfile << "me" << endl;
  outfile << "you" << endl;

  for(int i = 0; i < 300; i++){
    outfile << "h1 d1" << endl;
  }

  for(int i = 0; i < 300; i++){
    outfile << "undo" << endl;
  }

  for(int i = 0; i < 300; i++){
    outfile << "redo" << endl;
  }

  outfile.close();  
}
