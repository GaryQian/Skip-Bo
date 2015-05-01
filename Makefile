CC = g++
CXXFLAGS = -std=c++11 -pedantic -Wall -Wextra -O -g

bin: skipbo

test: DeckTest GameTest PlayerTest
	@echo "----------------------"
	@echo "DECK TESTS..."
	@./DeckTest
	@echo "GAME TESTS..."
	@./GameTest	
#	@echo "DISPLAY TESTS..."	
#	@./DisplayTest
	@echo "PLAYER TESTS..."
	@./PlayerTest
	@echo "ALL PASSED!"
	@echo "----------------------"

DeckTest: DeckTest.o Deck.o
	$(CC) $(CXXFLAGS) -o DeckTest DeckTest.o Deck.o Build.o Hand.o Draw.o Discard.o Stock.o

PlayerTest: PlayerTest.o Player.o
	$(CC) $(CXXFLAGS) -o PlayerTest PlayerTest.o Player.o Deck.o Build.o Hand.o Draw.o Discard.o Stock.o

GameTest: GameTest.o Game.o
	$(CC) $(CXXFLAGS) -o GameTest GameTest.o Move.o Game.o Player.o Display.o AI.o HumanPlayer.o Build.o Hand.o Draw.o Discard.o Stock.o Deck.o 

DeckTest.o: DeckTest.cpp Deck.h
	$(CC) $(CXXFLAGS) -c DeckTest.cpp

PlayerTest.o: PlayerTest.cpp Player.h
	$(CC) $(CXXFLAGS) -c PlayerTest.cpp

GameTest.o: GameTest.cpp Game.h Display.o
	$(CC) $(CXXFLAGS) -c GameTest.cpp

Deck.o: Deck.h Deck.cpp Draw.cpp Build.cpp Hand.cpp Discard.cpp Stock.cpp
	$(CC) $(CXXFLAGS) -c Deck.cpp Draw.cpp Build.cpp Hand.cpp Discard.cpp Stock.cpp

Display.o: Display.cpp Display.h Player.o Player.cpp HumanPlayer.cpp AI.cpp Player.h Build.o Build.cpp Deck.h Deck.cpp Deck.o Stock.cpp Stock.o Draw.cpp Draw.o Hand.cpp Hand.o
	$(CC) $(CXXFLAGS) -c Display.cpp -o Display.o

Game.o: Game.h Game.cpp Display.cpp Display.h Player.o Player.cpp Player.h Build.o Build.cpp Deck.cpp Deck.o Stock.cpp Move.o Stock.o Draw.cpp Draw.o Hand.cpp Hand.o
	$(CC) $(CXXFLAGS) -c Game.cpp -o Game.o

Move.o: Move.h Move.cpp
	$(CC) $(CXXFLAGS) -c Move.cpp -o Move.o

Player.o: Display.cpp Display.h Player.cpp Player.h Build.o Build.cpp Deck.cpp Deck.o Stock.cpp Stock.o Draw.cpp Draw.o Hand.cpp Hand.o AI.cpp HumanPlayer.cpp
	$(CC) $(CXXFLAGS) -c Player.cpp AI.cpp HumanPlayer.cpp

SkipBoMain.o: Game.h Game.cpp Display.cpp Display.h Player.o Player.cpp Player.h Build.o Build.cpp Deck.cpp Deck.o Stock.cpp Stock.o Draw.cpp Draw.o Hand.cpp Hand.o Move.o SkipBoMain.cpp
	$(CC) $(CXXFLAGS) -c SkipBoMain.cpp -o SkipBoMain.o

skipbo: Game.o Deck.o Display.o Game.o Player.o SkipBoMain.o
	$(CC) $(CXXFLAGS) Game.o Deck.o Stock.o Hand.o Build.o Draw.o AI.o HumanPlayer.o Discard.o Move.o Display.o Player.o SkipBoMain.o -o skipbo

clean: 
	rm -f *~ *.o *# *.gcov *.gch a.out DeckTest PlayerTest GameTest skipbo
