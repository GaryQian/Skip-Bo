/*
  Names: Kathleen Kusworo, Gary Qian, Sarah Sukardi, Matthew Tan
  Course: Intermediate Programming (AS.600.120)
  Date: 5/01/2015 (First Deadline), 5/08/2015 (Final Deadline)
  Assignment: Final Project-- Skip-Bo
  JHEDs: kkuswor1, gqian1, ssukard1, mtan13
  Email: (JHED)@jhu.edu

  This is the test file that tests all classes' methods.
*/

#include "GameTest.cpp"
#include "PlayerTest.cpp"
#include "DeckTest.cpp"
#include "DisplayTest.cpp"
#include <iostream>

using std::cout;
using std::endl;

int main() {
	//DECK TESTS
	cout << "Running Draw tests..." << endl;
	DrawTest::constructorTest();
	DrawTest::opsTest();
	DrawTest::takeCardTest();
	DrawTest::shuffleTest();
	DrawTest::moveTest();
	cout << "Passed Draw tests." << endl;

	cout << "Running Build tests..." << endl;
	BuildTest::constructorTest();
	BuildTest::opsTest();
	BuildTest::moveTest();
	cout << "Passed Build tests." << endl;

	cout << "Running Hand tests..." << endl;
	HandTest::constructorTest();
	HandTest::opsTest();
	HandTest::takeCardTest();
	HandTest::moveTest();
	cout << "Passed Hand tests." << endl;

	cout << "Running Stock tests..." << endl;
	StockTest::constructorTest();
	StockTest::opsTest();
	StockTest::takeCardTest();
	StockTest::moveTest();
	cout << "Passed Stock tests." << endl;

	cout << "Running Discard tests..." << endl;
	DiscardTest::constructorTest();
	DiscardTest::opsTest();
	DiscardTest::takeCardTest();
	DiscardTest::moveTest();
	cout << "Passed Discard tests." << endl << endl;
	

	//PLAYER TESTS
	cout << "Running Player tests..." << endl;

	cout << "Running HumanPlayer tests..." << endl;
	HumanPlayerTest::constructorTest();
	HumanPlayerTest::cardAccessorTests();
	HumanPlayerTest::hasWonTest();
	cout << "Passed HumanPlayer tests." << endl;

	cout << "Running AI tests..." << endl;
	AITest::constructorTest();
	AITest::containsTest();
	AITest::findTest();
	AITest::convertTest();
	cout << "Passed AI tests." << endl;

	cout << "Passed all Player tests." << endl << endl;
	
		
	//DISPLAY TESTS
	cout << "Running Display tests..." << endl;
	DisplayTest::testDisplay();
	cout << "Passed Display tests." << endl << endl;
        
	
	//GAME TESTS
	GameTest gt;
	cout << "Running constructor tests" << endl;
	gt.constructorTest();
	cout << "Passed constructor tests" << endl;
	cout << "Running process method tests" << endl;
	gt.ProcessTest();
	cout << "Passed process method tests" << endl;
	cout << "Running move method tests" << endl;
	gt.MoveTest();
	cout << "Passed move method tests" << endl;
	cout << "Running save/load method tests" << endl;
	gt.saveLoadTest();
	cout << "Passed save/load method tests" << endl;        
	cout << "Running undo tests" << endl;
	gt.undoTest();
	cout << "Passed undo tests" << endl;
	cout << "Running redo tests" << endl;
	gt.redoTest();
	cout << "Passed redo tests" << endl;
	return 0;
	
}
