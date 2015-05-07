/*Names: Kathleen Kusworo, Gary Qian, Sarah Sukardi, Matthew Tan
  Course: Intermediate Programming (AS.600.120)
  Date: 5/01/2015 (First Deadline), 5/08/2015 (Final Deadline)
  Assignment: Final Project-- Skip-Bo
  JHEDs: kkuswor1, gqian1, ssukard1, mtan13
  Email: (JHED)@jhu.edu
*/

#include "Display.h"
#include "Deck.h"
#include "Player.h"
#include <vector>
#include <iostream>
#include <string>
#include <cstdio>
#include <cassert>
#include <fstream>

using std::string;
using std::cout;
using std::vector;
using std::endl;

class DisplayTest {
  public:
	static bool fileeq(char lhsName[], char rhsName[]) {
		FILE* lhs = fopen(lhsName, "r");
		FILE* rhs = fopen(rhsName, "r");
		// don't compare if we can't open the files
		if (!lhs || !rhs) return false;

		bool match = true;
		// read until both of the files are done or there is a mismatch
		while (!feof(lhs) || !feof(rhs)) {
			
			if (feof(lhs) ||                  // lhs done first
				feof(rhs) ||                  // rhs done first
				(fgetc(lhs) != fgetc(rhs))) { // chars don't match
				match = false;
				break;
			}
		}
		fclose(lhs);
		fclose(rhs);
		return match;
	}



	static void testDisplay() {
		Display d;
		std::ofstream correct;
		correct.open ("correct.txt");
		
		vector<string*> out;
		
		string* temp;
		
		for (int i = 0; i < 60; ++i) {
			temp = new string(" ");
			out.push_back(temp);
		}
		
		temp = new string("                                      .++~");
		out.push_back(temp);
		temp = new string("                                   MMMMMMMMM.");
		out.push_back(temp);
		temp = new string("              8=          .  DMMM .MMMM DMMMM");
		out.push_back(temp);
		temp = new string("            MMMM   DM    MMM  MMM  MMMM  MMM+");
		out.push_back(temp);
		temp = new string("          MMMMMM  MMMD  MMMM. MMM8 MMMM  MMM.");
		out.push_back(temp);
		temp = new string("         MMMM.    MMMM MMMM.  MMMM MMMMMMMM  MMMM ");
		out.push_back(temp);
		temp = new string("        MMMMM$.   MMMM+MMM    MMMM  MMMMM.   MM+");
		out.push_back(temp);
		temp = new string("        MMMMMMMMM.MMMMMMMM.   MMMM  MMM.");
		out.push_back(temp);
		temp = new string("         MMMMMMMMMMMMM MMMMM  MMMM  MMMI");
		out.push_back(temp);
		temp = new string("          ..MMMMMM,MMM. MMMMMM:MMM. MMM.");
		out.push_back(temp);
		temp = new string("             MMMMM MMMO  MMMI .MM=");
		out.push_back(temp);
		temp = new string("          ..MMMMM  MMMM    .");
		out.push_back(temp);
		temp = new string("         .MMMMM    MM,.         :MMD.");
		out.push_back(temp);
		temp = new string("          MMM.                MMMMMMMM         .");
		out.push_back(temp);
		temp = new string("          ..  $MMMMMMMMMM    MMMMMMMMMM       .ZZZZZZZ");
		out.push_back(temp);
		temp = new string("               MMMMNMMMMMM. MMMM8..MMMMM      ZZZZZZZ,");
		out.push_back(temp);
		temp = new string("       ...     MMMM. .MMMM +MMM     MMMM      ZZZZZZZ I.");
		out.push_back(temp);
		temp = new string("   ~MMMMMM     MMMM? MMMM. MMMM     7MMM      ZZZZZZ7IIII.");
		out.push_back(temp);
		temp = new string("   MMMMMMM     MMMMMMMMMMM.DMMM     MMMM   MMMZZZZZIIIIIIII.");
		out.push_back(temp);
		temp = new string("   MMMMMMM     MMMMMMMMMMMM:MMMM.  MMMM.   MMMZZZZIIIIIIIII");
		out.push_back(temp);
		temp = new string("   ,MMMMMMM     MMMM.  MMMM$:MMMMMMMMM,    .MMZZZIIIIIIIII ");
		out.push_back(temp);
		temp = new string("    MMMMMMM     MMMM.  MMMM.  MMMMMMM        MMMIIIIIIIII");
		out.push_back(temp);
		temp = new string("    MMMMMMMM    MMMM$MMMMM      ..           .MMMIIIIII ");
		out.push_back(temp);
		temp = new string("     MMMMMMM    MMMMMMMM                      =MMMMIII.");
		out.push_back(temp);
		temp = new string("     ....       +MMM7.                         NMM. ..");
		out.push_back(temp);
		
		for (int i = 0; i < 2; ++i) {
			temp = new string(" ");
			out.push_back(temp);
		}
		
		temp = new string("=======Build Piles======");
		out.push_back(temp);
		
		////////////////////////////////////
		temp = new string("┌───┐ ┌───┐ ┌───┐ ┌───┐");
		out.push_back(temp);
		
		////////////////////////////////////
		temp = new string("│ 11│ │ 5 │ │   │ │ 1 │");
		out.push_back(temp);
		
		////////////////////////////////////
		temp = new string("└───┘ └───┘ └───┘ └───┘");
		out.push_back(temp);
		
		////////////////////////////////////
		temp = new string("=======================");
		out.push_back(temp);
		
		////////////////////////////////////
		temp = new string("Player ");
		*temp += d.convert(2);
		*temp += ": ";
		*temp += "test";
		*temp += "'s Turn";
		out.push_back(temp);
		
		////////////////////////////////////
		temp = new string("=======================");
		out.push_back(temp);
		
		////////////////////////////////////
		temp = new string("Hand:");
		out.push_back(temp);
		
		////////////////////////////////////
		temp = new string(" -1-   -2-   -3-   -4-   -5-");
		out.push_back(temp);
		
		////////////////////////////////////
		temp = new string("┌───┐ ┌───┐ ┌───┐ ┌───┐ ┌───┐");
		out.push_back(temp);
		
		////////////////////////////////////
		temp = new string("│ 1 │ │ 2 │ │ 3 │ │ 4 │ │ 10│");
		out.push_back(temp);
		
		////////////////////////////////////
		temp = new string("└───┘ └───┘ └───┘ └───┘ └───┘");
		out.push_back(temp);
		
		////////////////////////////////////
		temp = new string("Discard:");
		out.push_back(temp);
		
		////////////////////////////////////
		temp = new string(" -1-   -2-   -3-   -4-");
		out.push_back(temp);
		
		////////////////////////////////////
		temp = new string("┌───┐ ┌───┐ ┌───┐ ┌───┐");
		out.push_back(temp);
		
		////////////////////////////////////
		temp = new string("│   │ │   │ │   │ │   │");
		out.push_back(temp);
		
		////////////////////////////////////
		temp = new string("└───┘ └───┘ └───┘ └───┘");
		out.push_back(temp);
		
		////////////////////////////////////
		temp = new string("Stockpile:");
		out.push_back(temp);
		
		////////////////////////////////////
		temp = new string("┌───┐");
		out.push_back(temp);
		
		////////////////////////////////////
		temp = new string("│ 1 │");
		*temp += " 1 cards left";
		out.push_back(temp);
		
		////////////////////////////////////
		temp = new string("└───┘");
		out.push_back(temp);
		
		////////////////////////////////////
		temp = new string("└Your Move: ");
		out.push_back(temp);
		
		/*		
		for (unsigned long i = 0; i < out.size(); ++i) {
			if (i == out.size()) {
				correct << *(out.at(i));
			}
			else {
				correct << *(out.at(i)) << endl;
			}
		}
		
		for (int i = 0; i < (int) out.size(); ++i) {
			delete out.at(i);
		}
		
		correct.close();
	  
		std::ofstream output("test.txt");
		std::streambuf *coutbuf = std::cout.rdbuf();
		cout.rdbuf(output.rdbuf());
		
		vector<Build*> build;
		Build* buildtemp = new Build();
		build.push_back(buildtemp);
		buildtemp = new Build();
		build.push_back(buildtemp);
		buildtemp = new Build();
		build.push_back(buildtemp);
		buildtemp = new Build();
		build.push_back(buildtemp);
		buildtemp = new Build();
		build.push_back(buildtemp);
		for (int i = 1; i < 12; ++i) *(build.at(0)) += i;
		for (int i = 1; i < 6; ++i) *(build.at(1)) += i;
		for (int i = 1; i < 2; ++i) *(build.at(3)) += i;
		Stock* stock = new Stock();
		Draw* draw = new Draw();
		Player* player = new HumanPlayer("test", draw, &build, *stock);
		player->drawCards();
		player->hand.cards[0] = 1;
		player->hand.cards[1] = 2;
		player->hand.cards[2] = 3;
		player->hand.cards[3] = 4;
		player->hand.cards[4] = 10;
		player->stock.cards.push_back(1);
		
		d.display(player, build, 1);
		char test[9] = {"test.txt"};
		char corr[12] = {"correct.txt"};
		assert(fileeq(test, corr));
		cout.rdbuf(coutbuf);
		
		for (int i = 0; i < (int) build.size(); ++i) delete build.at(i);
		delete stock;
		delete player;*/
	}
};
/*
int main() {
	DisplayTest test;
	DisplayTest::testDisplay();
	return 0;
}*/
