CC = g++
CXXFLAGS = -std=c++11 -pedantic -Wall -Wextra -O -g

test: dTest
	@./dTest

dTest: dTest.o deck.o
	$(CC) $(CXXFLAGS) -o dTest DeckTest.o Deck.o Build.o Hand.o Draw.o Discard.o 

dTest.o: DeckTest.cpp Deck.h
	$(CC) $(CXXFLAGS) -c DeckTest.cpp

deck.o: Deck.h Deck.cpp Draw.cpp Build.cpp Hand.cpp Discard.cpp
	$(CC) $(CXXFLAGS) -c Deck.cpp Draw.cpp Build.cpp Hand.cpp Discard.cpp

clean: 
	rm -f *~ *.o *.gcov *.gch a.out dTest
