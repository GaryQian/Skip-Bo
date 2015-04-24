CC = g++
CXXFLAGS = -std=c++11 -pedantic -Wall -Wextra -O -g

bin: skipbo


test: DeckTest
	@./DeckTest

DeckTest: DeckTest.o Deck.o
	$(CC) $(CXXFLAGS) -o DeckTest DeckTest.o Deck.o Build.o Hand.o Draw.o Discard.o 

DeckTest.o: DeckTest.cpp Deck.h
	$(CC) $(CXXFLAGS) -c DeckTest.cpp

Deck.o: Deck.h Deck.cpp Draw.cpp Build.cpp Hand.cpp Discard.cpp
	$(CC) $(CXXFLAGS) -c Deck.cpp Draw.cpp Build.cpp Hand.cpp Discard.cpp

Display.o: Display.cpp Display.h Player.o Player.cpp Player.h Build.h Build.o Build.cpp Deck.h Deck.cpp Deck.o Stock.h Stock.cpp Stock.o Draw.h Draw.cpp Draw.o Hand.h Hand.cpp Hand.o
	$(CC) $(CXXFLAGS) -c Display.cpp Display.h -o Display.o

Game.o: Game.h Game.cpp Display.cpp Display.h Player.o Player.cpp Player.h Build.o Build.cpp Deck.cpp Deck.o Stock.cpp Stock.o Draw.cpp Draw.o Hand.cpp Hand.o
	$(CC) $(CXXFLAGS) -c Game.cpp Game.h -o Game.o

Player.o: Display.cpp Display.h Player.cpp Player.h Build.o Build.cpp Deck.cpp Deck.o Stock.cpp Stock.o Draw.cpp Draw.o Hand.cpp Hand.o
	$(CC) $(CXXFLAGS) -c Player.cpp Player.h -o Player.o

SkipBoMain.o: Game.h Game.cpp Display.cpp Display.h Player.o Player.cpp Player.h Build.o Build.cpp Deck.cpp Deck.o Stock.cpp Stock.o Draw.cpp Draw.o Hand.cpp Hand.o
	$(CC) $(CXXFLAGS) -c Display.cpp Display.h -o Display.o

skipbo: Game.o Deck.o Display.o Game.o Player.o SkipBoMain.o
	$(CC) $(CXXFLAGS) Game.o Deck.o Display.o Game.o Player.o SkipBoMain.o -o skipbo

clean: 
	rm -f *~ *.o *.gcov *.gch a.out DeckTest
