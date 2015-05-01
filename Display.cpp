#include "Player.h"
#include "Deck.h"
#include "Display.h"
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <chrono>
#include <thread>

using std::string;
using std::vector;
using std::ostringstream;
using std::cout;
using std::endl;

//Displays game onto the screen
void Display::display(Player* player, vector<Build*> build, int num) {
	vector<string> out;
	
	string* temp;
	
	//for (int i = 0; i < 60; ++i) {
		//temp = new string(" ");
		//out.push_back(*temp);
	//}
	
	intro();
	
	temp = new string("=======Build Piles======");
	out.push_back(*temp);
	
	////////////////////////////////////
	temp = new string("┌───┐ ┌───┐ ┌───┐ ┌───┐");
	out.push_back(*temp);
	
	////////////////////////////////////
	temp = new string("│ ");
	*temp += convert(build.at(0)->getTop(), *build.at(0));
	if (build.at(0)->getSize() % 12 >= 10 || (build.at(0)->getSize() % 12 == 0 && !build.at(0)->isEmpty())) {
		*temp += "│ │ ";
	}
	else *temp += " │ │ ";
	*temp += convert(build.at(1)->getTop(), *build.at(1));
	if (build.at(1)->getSize() % 12 >= 10 || (build.at(1)->getSize() % 12 == 0 && !build.at(1)->isEmpty())) {
		*temp += "│ │ ";
	}
	else *temp += " │ │ ";
	*temp += convert(build.at(2)->getTop(), *build.at(2));
	if (build.at(2)->getSize() % 12 >= 10 || (build.at(2)->getSize() % 12 == 0 && !build.at(2)->isEmpty())) {
		*temp += "│ │ ";
	}
	else *temp += " │ │ ";
	*temp += convert(build.at(3)->getTop(), *build.at(3));
	if (build.at(3)->getSize() % 12 >= 10 || (build.at(3)->getSize() % 12 == 0 && !build.at(3)->isEmpty())) {
		*temp += "│";
	}
	else *temp += " │";
	out.push_back(*temp);
	
	////////////////////////////////////
	temp = new string("└───┘ └───┘ └───┘ └───┘");
	out.push_back(*temp);
	
	////////////////////////////////////
	temp = new string("=======================");
	out.push_back(*temp);
	
	////////////////////////////////////
	temp = new string("Player ");
	*temp += convert(num + 1);
	*temp += ": ";
	*temp += player->getName();
	*temp += "'s Turn";
	out.push_back(*temp);
	
	////////////////////////////////////
	temp = new string("=======================");
	out.push_back(*temp);
	
	////////////////////////////////////
	temp = new string("Hand:");
	out.push_back(*temp);
	
	////////////////////////////////////
	switch(player->getHand().getSize()) {
	case 0: temp = new string("          No Cards"); break;
	case 1: temp = new string(" -1-"); break;
	case 2: temp = new string(" -1-   -2-"); break;
	case 3: temp = new string(" -1-   -2-   -3-"); break;
	case 4: temp = new string(" -1-   -2-   -3-   -4-"); break;
	case 5: temp = new string(" -1-   -2-   -3-   -4-   -5-"); break;
	}
	out.push_back(*temp);
	
	////////////////////////////////////
	switch(player->getHand().getSize()) {
	case 0: temp = new string(" "); break;
	case 1: temp = new string("┌───┐"); break;
	case 2: temp = new string("┌───┐ ┌───┐"); break;
	case 3: temp = new string("┌───┐ ┌───┐ ┌───┐"); break;
	case 4: temp = new string("┌───┐ ┌───┐ ┌───┐ ┌───┐"); break;
	case 5: temp = new string("┌───┐ ┌───┐ ┌───┐ ┌───┐ ┌───┐"); break;
	}
	out.push_back(*temp);
	
	////////////////////////////////////
	if (player->getHand().getSize() > 0) {
		temp = new string("│ ");
	}
	else temp = new string(" ");
	
	for (int i = 0; i < player->getHand().getSize(); ++i) {
		*temp += convert(player->getHand().at(i));
		if (i == player->getHand().getSize() - 1) {
			if (player->getHand().at(i) >= 10) {
				*temp += "│";
			}
			else *temp += " │";
		}
		else {
			if (player->getHand().at(i) >= 10) {
				*temp += "│ │ ";
			}
			else *temp += " │ │ ";
		}
	}
	out.push_back(*temp);
	
	////////////////////////////////////
	//temp = new string("└───┘ └───┘ └───┘ └───┘ └───┘");
	switch(player->getHand().getSize()) {
	case 0: temp = new string(" "); break;
	case 1: temp = new string("└───┘"); break;
	case 2: temp = new string("└───┘ └───┘"); break;
	case 3: temp = new string("└───┘ └───┘ └───┘"); break;
	case 4: temp = new string("└───┘ └───┘ └───┘ └───┘"); break;
	case 5: temp = new string("└───┘ └───┘ └───┘ └───┘ └───┘"); break;
	}
	out.push_back(*temp);
	
	////////////////////////////////////
	temp = new string("Discard:");
	out.push_back(*temp);
	
	////////////////////////////////////
	temp = new string(" -1-   -2-   -3-   -4-");
	out.push_back(*temp);
	
	////////////////////////////////////
	temp = new string("┌───┐ ┌───┐ ┌───┐ ┌───┐");
	out.push_back(*temp);
	
	////////////////////////////////////
	temp = new string("│ ");
	*temp += convert(player->getDiscard().at(0)->getTop());
	if (player->getDiscard().at(0)->getTop() >= 10) {
		*temp += "│ │ ";
	}
	else *temp += " │ │ ";
	*temp += convert(player->getDiscard().at(1)->getTop());
	if (player->getDiscard().at(1)->getTop() >= 10) {
		*temp += "│ │ ";
	}
	else *temp += " │ │ ";
	*temp += convert(player->getDiscard().at(2)->getTop());
	if (player->getDiscard().at(2)->getTop() >= 10) {
		*temp += "│ │ ";
	}
	else *temp += " │ │ ";
	*temp += convert(player->getDiscard().at(3)->getTop());
	if (player->getDiscard().at(3)->getTop() >= 10) {
		*temp += "│";
	}
	else *temp += " │";
	out.push_back(*temp);
	
	////////////////////////////////////
	temp = new string("└───┘ └───┘ └───┘ └───┘");
	out.push_back(*temp);
	
	////////////////////////////////////
	temp = new string("Stockpile:");
	out.push_back(*temp);
	
	////////////////////////////////////
	temp = new string("┌───┐");
	out.push_back(*temp);
	
	////////////////////////////////////
	temp = new string("│ ");
	if (!(player->getStock().isEmpty())) *temp += convert(player->getStock().getTop());
	else *temp += " ";
	if (player->getStock().getTop() >= 10) {
		*temp += "│ ";
	}
	else *temp += " │ ";
	*temp += convert(player->getStock().getSize());
	*temp += " cards left";
	out.push_back(*temp);
	
	////////////////////////////////////
	temp = new string("└───┘");
	out.push_back(*temp);
	
	////////////////////////////////////
	temp = new string("└Your Move: ");
	out.push_back(*temp);
	
	
	for (unsigned long i = 0; i < out.size(); ++i) {
		if (i == out.size()) {
			cout << out.at(i);
		}
		else {
			cout << out.at(i) << endl;
		}
	}
}

void Display::display(AI player, vector<Build*> build, int num) {
	display(player, build, num);
}

string Display::convert(int num) {
	if (num < 0) {
		return " ";
	}
	if (num == 0) {
		
		return "S";
	}
	ostringstream temp;
	temp << num;
	return temp.str();
}

string Display::convert(int num, Build build) {
	if (num < 0) {
		return " ";
	}
	if (num == 0) {
		
		return convert(build.getSize()%12);
	}
	ostringstream temp;
	temp << num;
	return temp.str();
}

void Display::intro() {
	vector<string> out;
	string* temp;
	
	for (int i = 0; i < 60; ++i) {
		temp = new string(" ");
		out.push_back(*temp);
	}
	
	temp = new string("                                      .++~");
	out.push_back(*temp);
	temp = new string("                                   MMMMMMMMM.");
	out.push_back(*temp);
	temp = new string("              8=          .  DMMM .MMMM DMMMM");
	out.push_back(*temp);
	temp = new string("            MMMM   DM    MMM  MMM  MMMM  MMM+");
	out.push_back(*temp);
	temp = new string("          MMMMMM  MMMD  MMMM. MMM8 MMMM  MMM.");
	out.push_back(*temp);
	temp = new string("         MMMM.    MMMM MMMM.  MMMM MMMMMMMM  MMMM ");
	out.push_back(*temp);
	temp = new string("        MMMMM$.   MMMM+MMM    MMMM  MMMMM.   MM+");
	out.push_back(*temp);
	temp = new string("        MMMMMMMMM.MMMMMMMM.   MMMM  MMM.");
	out.push_back(*temp);
	temp = new string("         MMMMMMMMMMMMM MMMMM  MMMM  MMMI");
	out.push_back(*temp);
	temp = new string("          ..MMMMMM,MMM. MMMMMM:MMM. MMM.");
	out.push_back(*temp);
	temp = new string("             MMMMM MMMO  MMMI .MM=");
	out.push_back(*temp);
	temp = new string("          ..MMMMM  MMMM    .");
	out.push_back(*temp);
	temp = new string("         .MMMMM    MM,.         :MMD.");
	out.push_back(*temp);
	temp = new string("          MMM.                MMMMMMMM         .");
	out.push_back(*temp);
	temp = new string("          ..  $MMMMMMMMMM    MMMMMMMMMM       .ZZZZZZZ");
	out.push_back(*temp);
	temp = new string("               MMMMNMMMMMM. MMMM8..MMMMM      ZZZZZZZ,");
	out.push_back(*temp);
	temp = new string("       ...     MMMM. .MMMM +MMM     MMMM      ZZZZZZZ I.");
	out.push_back(*temp);
	temp = new string("   ~MMMMMM     MMMM? MMMM. MMMM     7MMM      ZZZZZZ7IIII.");
	out.push_back(*temp);
	temp = new string("   MMMMMMM     MMMMMMMMMMM.DMMM     MMMM   MMMZZZZZIIIIIIII.");
	out.push_back(*temp);
	temp = new string("   MMMMMMM     MMMMMMMMMMMM:MMMM.  MMMM.   MMMZZZZIIIIIIIII");
	out.push_back(*temp);
	temp = new string("   ,MMMMMMM     MMMM.  MMMM$:MMMMMMMMM,    .MMZZZIIIIIIIII ");
	out.push_back(*temp);
	temp = new string("    MMMMMMM     MMMM.  MMMM.  MMMMMMM        MMMIIIIIIIII");
	out.push_back(*temp);
	temp = new string("    MMMMMMMM    MMMM$MMMMM      ..           .MMMIIIIII ");
	out.push_back(*temp);
	temp = new string("     MMMMMMM    MMMMMMMM                      =MMMMIII.");
	out.push_back(*temp);
	temp = new string("     ....       +MMM7.                         NMM. ..");
	out.push_back(*temp);
	
	for (int i = 0; i < 2; ++i) {
		temp = new string(" ");
		out.push_back(*temp);
	}
	
	
	for (unsigned long i = 0; i < out.size(); ++i) {
		if (i == out.size()) {
			cout << out.at(i);
		}
		else {
			cout << out.at(i) << endl;
		}
	}
	
}

void Display::change(Player* player, int num) {
	vector<string> out;
	string* temp;
	
	for (int i = 0; i < 60; ++i) {
		temp = new string(" ");
		out.push_back(*temp);
	}
	temp = new string("=====================================================");
	out.push_back(*temp);
	temp = new string("=        ██       Switching Players!       ██       =");
	out.push_back(*temp);
	temp = new string("=====================================================");
	out.push_back(*temp);
	temp = new string("");
	out.push_back(*temp);
	
	temp = new string("Player ");
	*temp += convert(num + 1);
	*temp += ": ";
	*temp += player->getName();
	*temp += "'s Turn";
	out.push_back(*temp);
	
	temp = new string("");
	out.push_back(*temp);
	temp = new string("=====================================================");
	out.push_back(*temp);
	temp = new string("=                                                   =");
	out.push_back(*temp);
	temp = new string("=====================================================");
	out.push_back(*temp);
	
	for (unsigned long i = 0; i < out.size(); ++i) {
		if (i == out.size()) {
			cout << out.at(i);
		}
		else {
			cout << out.at(i) << endl;
		}
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(200));	
	///////////////////////////////////////////////////////
	out.clear();
	for (int i = 0; i < 60; ++i) {
		temp = new string(" ");
		out.push_back(*temp);
	}
	temp = new string("=====================================================");
	out.push_back(*temp);
	temp = new string("=                 Switching Players!                =");
	out.push_back(*temp);
	temp = new string("=====================================================");
	out.push_back(*temp);
	temp = new string("");
	out.push_back(*temp);
	
	temp = new string("Player ");
	*temp += convert(num + 1);
	*temp += ": ";
	*temp += player->getName();
	*temp += "'s Turn";
	out.push_back(*temp);
	
	temp = new string("");
	out.push_back(*temp);
	temp = new string("=====================================================");
	out.push_back(*temp);
	temp = new string("=                  Switching Players!               =");
	out.push_back(*temp);
	temp = new string("=====================================================");
	out.push_back(*temp);
	
	for (unsigned long i = 0; i < out.size(); ++i) {
		if (i == out.size()) {
			cout << out.at(i);
		}
		else {
			cout << out.at(i) << endl;
		}
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(200));	
	///////////////////////////////////////////////////////
	out.clear();
	for (int i = 0; i < 60; ++i) {
		temp = new string(" ");
		out.push_back(*temp);
	}
	temp = new string("=====================================================");
	out.push_back(*temp);
	temp = new string("=        ██       Switching Players!       ██       =");
	out.push_back(*temp);
	temp = new string("=====================================================");
	out.push_back(*temp);
	temp = new string("");
	out.push_back(*temp);
	
	temp = new string("Player ");
	*temp += convert(num + 1);
	*temp += ": ";
	*temp += player->getName();
	*temp += "'s Turn";
	out.push_back(*temp);
	
	temp = new string("");
	out.push_back(*temp);
	temp = new string("=====================================================");
	out.push_back(*temp);
	temp = new string("=                                                   =");
	out.push_back(*temp);
	temp = new string("=====================================================");
	out.push_back(*temp);
	
	for (unsigned long i = 0; i < out.size(); ++i) {
		if (i == out.size()) {
			cout << out.at(i);
		}
		else {
			cout << out.at(i) << endl;
		}
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	///////////////////////////////////////////////////////
	out.clear();
	for (int i = 0; i < 60; ++i) {
		temp = new string(" ");
		out.push_back(*temp);
	}
	temp = new string("=====================================================");
	out.push_back(*temp);
	temp = new string("=                 Switching Players!                =");
	out.push_back(*temp);
	temp = new string("=====================================================");
	out.push_back(*temp);
	temp = new string("");
	out.push_back(*temp);
	
	temp = new string("Player ");
	*temp += convert(num + 1);
	*temp += ": ";
	*temp += player->getName();
	*temp += "'s Turn";
	out.push_back(*temp);
	
	temp = new string("");
	out.push_back(*temp);
	temp = new string("=====================================================");
	out.push_back(*temp);
	temp = new string("=                  Switching Players!               =");
	out.push_back(*temp);
	temp = new string("=====================================================");
	out.push_back(*temp);
	
	for (unsigned long i = 0; i < out.size(); ++i) {
		if (i == out.size()) {
			cout << out.at(i);
		}
		else {
			cout << out.at(i) << endl;
		}
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	out.clear();
	for (int i = 0; i < 60; ++i) {
		temp = new string(" ");
		out.push_back(*temp);
	}
	temp = new string("=====================================================");
	out.push_back(*temp);
	temp = new string("=        ██       Switching Players!       ██       =");
	out.push_back(*temp);
	temp = new string("=====================================================");
	out.push_back(*temp);
	temp = new string("");
	out.push_back(*temp);
	
	temp = new string("Player ");
	*temp += convert(num + 1);
	*temp += ": ";
	*temp += player->getName();
	*temp += "'s Turn";
	out.push_back(*temp);
	
	temp = new string("");
	out.push_back(*temp);
	temp = new string("=====================================================");
	out.push_back(*temp);
	temp = new string("=                                                   =");
	out.push_back(*temp);
	temp = new string("=====================================================");
	out.push_back(*temp);
	
	for (unsigned long i = 0; i < out.size(); ++i) {
		if (i == out.size()) {
			cout << out.at(i);
		}
		else {
			cout << out.at(i) << endl;
		}
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	
}
