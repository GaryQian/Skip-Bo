﻿#include "Player.h"
#include "Build.h"
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

using std::string;
using std::vector;
using std::ostream;
using std::cout;
using std::endl;

static void Display::display(Player player, vector<Build> build, int num) {
	vector<string> out;
	
	string temp;
	
	temp = new string("=======Build Piles======");
	out.push_back(temp);
	
	////////////////////////////////////
	temp = new string("┌───┐ ┌───┐ ┌───┐ ┌───┐");
	out.push_back(temp);
	
	////////////////////////////////////
	temp = new string("│ ");
	temp += convert(build[0].getTop());
	if (build[0].getTop() >= 10) {
		temp += "│ │ ";
	}
	else temp += " │ │ ";
	temp += convert(build[1].getTop());
	if (build[1].getTop() >= 10) {
		temp += "│ │ ";
	}
	else temp += " │ │ ";
	temp += convert(build[2].getTop());
	if (build[2].getTop() >= 10) {
		temp += "│ │ ";
	}
	else temp += " │ │ ";
	temp += convert(build[3].getTop());
	if (build[3].getTop() >= 10) {
		temp += "│";
	}
	else temp += " │";
	out.push_back(temp);
	
	////////////////////////////////////
	temp = new string("└───┘ └───┘ └───┘ └───┘");
	out.push_back(temp);
	
	////////////////////////////////////
	temp = new string("=======================");
	out.push_back(temp);
	
	////////////////////////////////////
	temp = new string("Player ");
	temp += convert(num);
	temp += ": ";
	temp += player.name;
	temp += "'s Turn"
	out.push_back(temp);
	
	////////////////////////////////////
	temp = new string("=======================");
	out.push_back(temp);
	
	////////////////////////////////////
	temp = new string("Hand:");
	out.push_back(temp);
	
	////////////////////////////////////
	switch(player.hand.getSize()) {
		case 0: temp = new string("          No Cards"); break;
		case 1: temp = new string(" -1-"); break;
		case 2: temp = new string(" -1-   -2-"); break;
		case 3: temp = new string(" -1-   -2-   -3-"); break;
		case 4: temp = new string(" -1-   -2-   -3-   -4-"); break;
		case 5: temp = new string(" -1-   -2-   -3-   -4-   -5-"); break;
	}
	out.push_back(temp);
	
	////////////////////////////////////
	switch(player.hand.getSize()) {
		case 0: temp = new string(" "); break;
		case 1: temp = new string("┌───┐"); break;
		case 2: temp = new string("┌───┐ ┌───┐"); break;
		case 3: temp = new string("┌───┐ ┌───┐ ┌───┐"); break;
		case 4: temp = new string("┌───┐ ┌───┐ ┌───┐ ┌───┐"); break;
		case 5: temp = new string("┌───┐ ┌───┐ ┌───┐ ┌───┐ ┌───┐"); break;
	}
	out.push_back(temp);
	
	////////////////////////////////////
	if (player.hand.getSize() > 0) {
		temp = new string("│ ");
	}
	else temp = new string(" ");
	
	for (int i = 0; i < player.hand.getSize(); ++i) {
		temp += convert(player.hand.at(i));
		if (i == player.hand.getSize() - 1) {
			if (player.hand.at(i) >= 10) {
				temp += "│";
			}
			else temp += " │";
		}
		else {
			if (player.hand.at(i) >= 10) {
				temp += "│ │ ";
			}
			else temp += " │ │ ";
		}
	}
	out.push_back(temp);
	
	////////////////////////////////////
	temp = new string("└───┘ └───┘ └───┘ └───┘ └───┘");
	switch(player.hand.getSize()) {
		case 0: temp = new string(" "); break;
		case 1: temp = new string("└───┘"); break;
		case 2: temp = new string("└───┘ └───┘"); break;
		case 3: temp = new string("└───┘ └───┘ └───┘"); break;
		case 4: temp = new string("└───┘ └───┘ └───┘ └───┘"); break;
		case 5: temp = new string("└───┘ └───┘ └───┘ └───┘ └───┘"); break;
	}
	out.push_back(temp);
	
	////////////////////////////////////
	temp = new string("Discard:");
	out.push_back(temp);
	
}

static string Display::convert(int num) {
	if (num < 0) {
		return " ";
	}
	if (num == 0) {
		return "S";
	}
	ostream temp;
	temp << int;
	return temp.str();
}
