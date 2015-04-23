CC = g++
CXXFLAGS = -std=c++11 -pedantic -Wall -Wextra -O -g

deckTest: DeckTest.cpp deck.o
	$(CC) $(CXXFLAGS) DeckTest.cpp

deck.o: Deck.h Deck.cpp Draw.h Draw.cpp Build.h Build.cpp Hand.h Hand.cpp Discard.h Discard.cpp
	$(CC) $(CXXFLAGS) -c Deck.cpp Draw.cpp Build.cpp Hand.cpp Discard.cpp

clean: 
	rm -f *~ *.o *.gcov a.out
