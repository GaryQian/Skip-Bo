CC = g++
CXXFLAGS = -std=c++11 -pedantic -Wall -Wextra -O -g

bin: skipbo

test: SkipBoTest
	@echo "----------------------"
	@./SkipBoTest
	@echo " "

	@echo "ALL TESTS PASSED!"
	@echo "----------------------"

SkipBoTest: SkipBoTest.o DisplayTest.o PlayerTest.o GameTest.o DeckTest.o Deck.o Build.o Hand.o Draw.o Stock.o Move.o Game.o Player.o Display.o AI.o HumanPlayer.o Discard.o
	$(CC) $(CXXFLAGS) -o SkipBoTest SkipBoTest.o DisplayTest.o PlayerTest.o GameTest.o DeckTest.o Deck.o Build.o Hand.o Draw.o Stock.o Move.o Game.o Player.o Display.o AI.o HumanPlayer.o Discard.o

SkipBoTest.o: SkipBo.cpp DisplayTest.cpp PlayerTest.cpp GameTest.cpp DeckTest.cpp
	$(CC) $(CXXFLAGS) -c SkipBo.cpp -o SkipBoTest.o

DeckTest: DeckTest.o Deck.o
	$(CC) $(CXXFLAGS) -o DeckTest DeckTest.o Deck.o Build.o Hand.o Draw.o Discard.o Stock.o

PlayerTest: PlayerTest.o Player.o
	$(CC) $(CXXFLAGS) -o PlayerTest PlayerTest.o Player.o Deck.o Build.o Hand.o Draw.o Discard.o Stock.o AI.o HumanPlayer.o

GameTest: GameTest.o Game.o
	$(CC) $(CXXFLAGS) -o GameTest GameTest.o Move.o Game.o Player.o Display.o AI.o HumanPlayer.o Build.o Hand.o Draw.o Discard.o Stock.o Deck.o 

DeckTest.o: DeckTest.cpp Deck.h
	$(CC) $(CXXFLAGS) -c DeckTest.cpp

PlayerTest.o: PlayerTest.cpp Player.h
	$(CC) $(CXXFLAGS) -c PlayerTest.cpp

GameTest.o: GameTest.cpp Game.h Exception.h Display.o
	$(CC) $(CXXFLAGS) -c GameTest.cpp

DisplayTest: DisplayTest.o Display.o Player.o Deck.o Display.h
	$(CC) $(CXXFLAGS) DisplayTest.o Display.o Player.o Deck.o Build.o Hand.o Draw.o Discard.o Stock.o AI.o HumanPlayer.o -o DisplayTest

DisplayTest.o: DisplayTest.cpp Display.o Player.o Deck.o Display.h
	$(CC) $(CXXFLAGS) -c DisplayTest.cpp

Deck.o: Deck.h Deck.cpp Draw.cpp Build.cpp Hand.cpp Discard.cpp Stock.cpp
	$(CC) $(CXXFLAGS) -c Deck.cpp Draw.cpp Build.cpp Hand.cpp Discard.cpp Stock.cpp

Display.o: Display.cpp Display.h Player.o Player.cpp HumanPlayer.cpp AI.cpp Player.h Build.o Build.cpp Deck.h Deck.cpp Deck.o Stock.cpp Stock.o Draw.cpp Draw.o Hand.cpp Hand.o Game.o Game.h
	$(CC) $(CXXFLAGS) -c Display.cpp -o Display.o

Game.o: Game.h Game.cpp Display.cpp Display.h Player.o Player.cpp Player.h Build.o Build.cpp Deck.cpp Deck.o Stock.cpp Move.o Stock.o Draw.cpp Draw.o Hand.cpp Hand.o Exception.h
	$(CC) $(CXXFLAGS) -c Game.cpp -o Game.o

Move.o: Move.h Move.cpp
	$(CC) $(CXXFLAGS) -c Move.cpp -o Move.o

Player.o: Display.cpp Display.h Player.cpp Player.h Build.o Build.cpp Deck.cpp Deck.o Stock.cpp Stock.o Draw.cpp Draw.o Hand.cpp Hand.o AI.cpp HumanPlayer.cpp Exception.h
	$(CC) $(CXXFLAGS) -c Player.cpp AI.cpp HumanPlayer.cpp

SkipBoMain.o: Game.h Game.cpp Display.cpp Display.h Player.o Player.cpp Player.h Build.o Build.cpp Deck.cpp Deck.o Stock.cpp Stock.o Draw.cpp Draw.o Hand.cpp Hand.o Move.o Exception.h SkipBoMain.cpp
	$(CC) $(CXXFLAGS) -c SkipBoMain.cpp -o SkipBoMain.o

skipbo: Game.o Deck.o Display.o Game.o Player.o SkipBoMain.o
	$(CC) $(CXXFLAGS) Game.o Deck.o Stock.o Hand.o Build.o Draw.o AI.o HumanPlayer.o Discard.o Move.o Display.o Player.o SkipBoMain.o -o skipbo

speed: 	testGen
	@echo "Running undo/redo speed test..."
	@./testGen
	@make clean
	@make skipbo
	@./skipbo < test_speed.txt
	@echo "Finished."

testGen: testGen.cpp 
	$(CC) $(CXXFLAGS) -o testGen testGen.cpp

clean: 
	rm -f *~ *.o *# *.gcov *.gch *move_* a.out DeckTest PlayerTest GameTest skipbo DisplayTest SkipBoTest testGen

