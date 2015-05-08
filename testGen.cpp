/*
 * Names: Kathleen Kusworo, Gary Qian, Sarah Sukardi, Matthew Tan
 * Course: Intermediate Programming (AS.600.120)
 * Date: 5/01/2015 (First Deadline), 5/08/2015 (Final Deadline)
 * Assignment: Final Project-- Skip-Bo
 * JHEDs: kkuswor1, gqian1, ssukard1, mtan13
 * Email: (JHED)@jhu.edu
 *
 * This file generates a text file called test_speed.txt, which
 * basically feeds in commands to the skip-bo game. This version calls
 * for 4 players to keep discarding the first card in their hand to
 * the first discard pile, for 1000 times. Then we call undo for 1000
 * times, and redo 1000 times, and finishes the test session using
 * save. By calling make speed on the command line, the user can see
 * how the game's speed is not affected by calling undo/redo
 */

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
  outfile << "0" << endl;

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
