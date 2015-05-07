/*Names: Kathleen Kusworo, Gary Qian, Sarah Sukardi, Matthew Tan
  Course: Intermediate Programming (AS.600.120)
  Date: 5/01/2015 (First Deadline), 5/08/2015 (Final Deadline)
  Assignment: Final Project-- Skip-Bo
  JHEDs: kkuswor1, gqian1, ssukard1, mtan13
  Email: (JHED)@jhu.edu
*/

//#include "Game.h"
#include "Display.h"
#include "Exception.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <exception>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::invalid_argument;
using std::ostringstream;

int main(){
  Game* game;
  string save;
  string input;
  vector<string> names;
  int players;
  Display d;
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
    try{
      game->load_game(input);
    }
    catch(invalid_argument & e){
      cout << "File not found!\n" << endl;
    }
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
      d.display(game->getPlayer(), game->getBuild(), game->getPlayerNumber(), game);
      
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
	  oss << "move_" << game -> getNumMove();
	  game -> save_game(oss.str());
	  oss.str("");
	  oss.clear();

	  //get the user's input move
	  input = game->getPlayer()->getMove();

	  //process the input, throws an exception if invalid
	  //if not, then goes on to play the move
	  game->process(input);

	  //display the game after change has been made
	  d.display(game->getPlayer(), game->getBuild(), game->getPlayerNumber(), game);
	}
	//catch any exception thrown by a user's invalid move
	catch(invalid_argument& e){
	  cout << e.what() << endl;
	}

	//if the player's hand is empty, refill it
	if (game->getPlayer()->getHand().getSize()==0){
	  game->refill();
	}
	//recompute the choices that the player can make
	choices = game->canMove();
      }

      //if no more possible moves, display the game
      d.display(game->getPlayer(), game->getBuild(), game->getPlayerNumber(), game);   
      
      //save game state
      oss << "move_" << game -> getNumMove();
      game -> save_game(oss.str());
      oss.str("");
      oss.clear();


      //keep looping this instruction until the player puts a card into the discard pile
      //once they did, process method will throw an integer that is caught by the catch
      //block for the outermost try block
      while(true){
	cout << "No moves left.\nPlease move card to discard pile to end turn\n";	
	input= game->getPlayer()->getMove();
	try {
	  game->process(input);
	  
	  //recompute the choices that the player can make, in case
	  //player chooses to undo and loads a previous save state
	  choices = game->canMove();

	  //if now there are choices, break out of this while loop
	  if(!choices.empty()){
	    d.display(game->getPlayer(), game->getBuild(), game->getPlayerNumber(), game);   
	    break;
	  }
	}
	//catches invalid move input, but doesn't catch the integer thrown
	//when the user puts a card in the discard pile
	catch (invalid_argument& e){
	  cout << e.what() << endl;
	}
      }
    }
    //once integer is thrown, it meanst the player has ended their turn by putting
    //a card in the discard pile. Move to next player's turn
    catch (const TurnEndException & e){
      d.display(game->getPlayer(), game->getBuild(), game->getPlayerNumber(), game);
      //d.change(game->getNextPlayer(), game->getNextPlayerNumber());
      cout << e.what() << endl;
      game->nextTurn();
      game->refill();
    }
    //catches the character thrown if the user types in "save"
    //will save game and end the game
    catch (const SaveException & e){
	cout << "File successfully saved\n" << endl;
	delete game;
	return 0;
    }
  }
  delete game;
  //system("rm move_*");
}
