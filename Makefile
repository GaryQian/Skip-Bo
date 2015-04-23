CC = g++
CXXFLAGS = -std=c++11 -pedantic -Wall -Wextra -O -g

deck.o: Deck.h Deck.cpp Draw.h Draw.cpp
	$(CC) $(CXXFLAGS) -c Deck.cpp Draw.cpp 

clean: 
	rm -f *~ *.o *.gcov a.out
