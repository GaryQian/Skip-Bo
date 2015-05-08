#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>

class TurnEndException: public std::exception{
 public:
  virtual const char* what() const throw();
};

class SaveException: public std::exception{
 public:  
  virtual const char* what() const throw();
};

#endif