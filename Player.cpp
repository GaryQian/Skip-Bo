#include "Player.h"

#include <string>
#include <vector>

using std::string;
using std::vector;

Player::Player(string name, Draw* draw, vector<Build>* build) {
  this->draw = *draw;
  this->name = name;
  this->build = build;
  deal();	
}

//do we have to accomodate for when there are more than 4 players; in which there would be 20 cards/player?
void Player::deal(int playerNum) 
{
  if (playerNum <= 4 && playerNum >= 1)
    {
      stock += draw.take(30);
    }
  if (playerNum > 4)
    {
      stock += draw.take(20);
    }
}

bool Player::hasWon()
{
  if (stock.isEmpty())
    return true;
  return false;
}

bool Player::playCard(Deck a, Deck b)
{
  if (a.move(b))
    return true;
  return false;
}

bool Player::playCard(Deck b, int num)
{
  if (hand.move(Deck b, int num))
    return true;
  return false;
}

string Player::getName()
{
  return name;
}

Hand Player::getHand()
{
  return hand;
}

vector<Discard> getDiscard()
{
  return discard;
}

vector<int> getStock()
{
  return stock;
}
