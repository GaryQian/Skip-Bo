#include <fstream>
#include <iostream>

using std::ofstream;
using std::endl;

int main(void){
  ofstream outfile("test_speed.txt");
  
  outfile << "no" << endl;
  outfile << "4" << endl;
  outfile << "me" << endl;
  outfile << "you" << endl;
  outfile << "him" << endl;
  outfile << "her" << endl;

  for(int i = 0; i < 1000; i++){
    outfile << "h1 d1" << endl;
  }

  for(int i = 0; i < 1000; i++){
    outfile << "undo" << endl;
  }

  for(int i = 0; i < 1000; i++){
    outfile << "redo" << endl;
  }

  outfile << "save" << endl;
  outfile << "test_speed" << endl;

  outfile.close();  
}
