/*Names: Kathleen Kusworo, Gary Qian, Sarah Sukardi, Matthew Tan
  Course: Intermediate Programming (AS.600.120)
  Date: 5/01/2015 (First Deadline), 5/08/2015 (Final Deadline)
  Assignment: Final Project-- Skip-Bo
  JHEDs: kkuswor1, gqian1, ssukard1, mtan13
  Email: (JHED)@jhu.edu
*/

#include "Game.h"
#include "Display.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <exception>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::exception;
using std::ostringstream;

int main(){
  Game* game;
  string save;
  string input;
  vector<string> names;
  int players;
  Display d;
  int numMove = 1;
  ostringstream oss;

  //Prompts user to enter in a game
  cout << "Welcome to Skip-Bo!" << endl;
  d.intro();
  cout << "Would you like to load a saved game?" << endl;

  //Loads the game	
  cin >> save;
  std::transform(save.begin(), save.end(), save.begin(), ::tolower);
  if (save == "yes" || save == "y" || save == "ye" || save == "1" || save.at(0) == 'y' || save.at(0) == '1') {
    cout << "Please enter the savefile name:" << endl;
    cin >> input;
    game = new Game();
    game->load_game(input);
  }
  else {
    //Else, begins a new game
		
    cout << "How many players? (Enter Integer):" << endl;
    cin >> players;
		
    names.resize(players);
		
    for(int i = 0; i < players; i++){
      cout << "Enter name of player " << i+1 << ". If player is an AI, prefix with \"AI\"." << endl;
      cin >> names[i];
    }
		
    game = new Game(names);
    game->nextTurn();
    game->refill();
  }

  cin.ignore();

  //while game hasn't ended
  while (!game->hasEnded()) {
    try{
      //display the game
      d.display(game->getPlayer(), game->getBuild(), game->getPlayerNumber());
      
      //create a vector of choices that the player ca make
      vector<Move*> choices = game->canMove();

      //while the player still has a choice of moves
      while (choices.size()) {
	try{  
	  //delete the vector of choices
	  for(unsigned long i = 0; i < choices.size(); i++){
	    delete choices.at(i);
	  }

	  //save game state
	  oss << "move_" << numMove;
	  game -> save_game(oss.str());
	  oss.str("");
	  oss.clear();

	  //get the user's input move
	  input = game->getPlayer()->getMove();

	  //process the input, throws an exception if invalid
	  //if not, then goes on to play the move
	  game->process(input);

	  //display the game after change has been made
	  d.display(game->getPlayer(), game->getBuild(), game->getPlayerNumber());
	}
	//catch any exception thrown by a user's invalid move
	catch(exception& e){
	  cout << e.what() << endl;

	  //decrement numMove - since move is invalid, there is nothing to
	  //undo and we can overwrite the previous game state
	  //numMove--;
	}

	//if move is valid, then increment numMove
	numMove++;

	//if the player's hand is empty, refill it
	if (game->getPlayer()->getHand().getSize()==0){
	  game->refill();
	}
	//recompute the choices that the player can make
	choices = game->canMove();
      }

      //if no more possible moves, display the game
      d.display(game->getPlayer(), game->getBuild(), game->getPlayerNumber());   
      
      //keep looping this instruction until the player puts a card into the discard pile
      //once they did, process method will throw an integer that is caught by the catch
      //block for the outermost try block
      while(true){
	cout << "No moves left.\nPlease move card to discard pile to end turn\n";	
	input= game->getPlayer()->getMove();
	try{
	  game->process(input);
	}
	//catches invalid move input, but doesn't catch the integer thrown
	//when the user puts a card in the discard pile
	catch (exception& e){
	  cout << e.what() << endl;
	}
      }
    }
    //once integer is thrown, it meanst the player has ended their turn by putting
    //a card in the discard pile. Move to next player's turn
    catch (int a){
      d.display(game->getPlayer(), game->getBuild(), game->getPlayerNumber());
      //d.change(game->getNextPlayer(), game->getNextPlayerNumber());
      cout << "Turn end\n" << endl;
      game->nextTurn();
      game->refill();

      //reset numMove to 1
      numMove = 1;
    }
    //catches the character thrown if the user types in "save"
    //will save game and end the game
    catch (char c){
      if(c == 's') {
	cout << "File successfully saved\n" << endl;
	delete game;
	return 0;
      }
      else if(c == 'u'){
	try {game -> undo(numMove);}
	catch (exception & e){ cout << e.what() << endl;}
      }
    }
  }
  delete game;
}
