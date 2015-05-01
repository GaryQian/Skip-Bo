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

int main(){
  Game* game;
  string save;
  string input;
  vector<string> names;
  int players;
  Display d;
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
      std::getline(names[i], cin);
    }
    
    game = new Game(names);
  }
  
  cin.ignore();
  
  
  while (!game->hasEnded()) {
    game->nextTurn();
    try{
      d.display(game->getPlayer(), game->getBuild(), game->getPlayerNumber());
      vector<Move*> choices = game->canMove();
      while (choices.size()) {
	try{  
	  for(unsigned long i = 0; i < choices.size(); i++){
	    delete choices.at(i);
	  }
	  input = game->getPlayer()->getMove();
	  game->process(input);
	  game->refill();
	  d.display(game->getPlayer(), game->getBuild(), game->getPlayerNumber());
	}
	catch(exception& e){
	  cout << e.what() << endl;
	}
      }
      d.display(game->getPlayer(), game->getBuild(), game->getPlayerNumber());   
      while(true){
	cout << "No moves left.\nPlease move card to discard pile to end turn\n";	
	input= game->getPlayer()->getMove();
	try{
	  game->process(input);
	}
	catch (exception& e){
	  cout << e.what() << endl;
	}
      }
    }
    catch (int a){
      d.display(game->getPlayer(), game->getBuild(), game->getPlayerNumber());
	  //d.change(game->getNextPlayer(), game->getNextPlayerNumber());
      cout << "Turn end\n" << endl;
    }
    catch (char c){
      cout << "File successfully saved\n" << endl;
      delete game;
      return 0;
    }
  }
  delete game;
}
