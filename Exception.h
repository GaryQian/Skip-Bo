/*
  Names: Kathleen Kusworo, Gary Qian, Sarah Sukardi, Matthew Tan
  Course: Intermediate Programming (AS.600.120)
  Date: 5/01/2015 (First Deadline), 5/08/2015 (Final Deadline)
  Assignment: Final Project-- Skip-Bo
  JHEDs: kkuswor1, gqian1, ssukard1, mtan13
  Email: (JHED)@jhu.edu

  This header file declares the custom exceptions thrown in our
  skip-bo program
*/

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>

//TurnEndException marks the end of a player's turn - thrown when a
//player discards a card
class TurnEndException: public std::exception{
 public:
  virtual const char* what() const throw();
};

//SaveException indicates the player wants to save the game - thrown
//when a player types in "save" during gameplay
class SaveException: public std::exception{
 public:  
  virtual const char* what() const throw();
};

//GameEndException indicats a player has won - thrown when a player's
//stock pile reaches zero
class GameEndException: public std::exception{
 public:
  virtual const char* what() const throw();
};

#endif
