#include"textdisplay.h"
#include"../subject.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include "../globalSettings.h"
#include "../enemy/enemy.h"
#include "../enemy/enemy.h"
#include "../enemy/warlock.h"
#include "../enemy/vindicator.h"
#include "../enemy/mercenary.h"
#include "../enemy/ninja.h"
#include "../enemy/defender.h"
#include "../enemy/wizard.h"
#include "../enemy/xenosite.h"
#include "../enemy/tankmaster.h"
using namespace std;

TextDisplay :: TextDisplay(int width, int height)
  :width{width}, height{height} {
    for (int i = 0; i < height; i++) {
        vector<char>tempV;
        for (int j = 0; j < width; j++) {
            tempV.emplace_back('.');
        }
        theDisplay.emplace_back(tempV);
    }
}

void TextDisplay :: doNotify(Subject &whoNotified) {
    int xc, yc;
    whoNotified.getPos(xc, yc);
    //cerr << "yc" <<yc << "xc" <<xc<<" ";
    theDisplay[yc][xc] = whoNotified.getDisplay();
}

void TextDisplay::doPrint(bool hasSmartPointer, ostream& out,
    vector<string>elines) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if ((theDisplay[i][j] == global__displayStair) && (!hasSmartPointer)) {
                //the one smartPointer grid
                if (global__modded){
		    if (!global__hacker) out << global__displayNormalCell ;
                    else out << global__displayNormalCell;
                } else {
                    out << global__displayNormalCell;
		}
            } else { //other grid
		if (global__modded) {
		    if ((i == 0) || (i == height - 1) || (j == 0) ||
                        (j == width - 1)){
		        if (theDisplay[i][j] != global__displayPlayer){
                            out << theDisplay[i][j] ;
			} else {
			    out << theDisplay[i][j] ;
			}
		    } else if(theDisplay[i][j] == global__displayGold){ 
                        out << global__displayGold;
                    } else if (theDisplay[i][j] == global__displayPotion){ 
                        out << global__displayPotion;
                    } else if (theDisplay[i][j] == global__displayPlayer){ 
                        out << global__displayPlayer;
                    } else if ((theDisplay[i][j] == global__displayDefender)||
			       (theDisplay[i][j] == global__displayWarlock)||
			       (theDisplay[i][j] == global__displayXenosite)||
			       (theDisplay[i][j] == global__displayVindicator)||
			       (theDisplay[i][j] == global__displayNinja)||
			       (theDisplay[i][j] == global__displayMercenary)||
			       (theDisplay[i][j] == global__displayTankmaster)||
			       (theDisplay[i][j] == global__displayWizard)) {
                        out << theDisplay[i][j] ;
                    } else if (theDisplay[i][j] == global__displayStair){ 
                        out << theDisplay[i][j];
                    } else if (theDisplay[i][j] == global__displaySmartPtr){
                        out << theDisplay[i][j];
                    } else if (theDisplay[i][j] == global__displayForceShield){
                        out << theDisplay[i][j];
                    } else if (theDisplay[i][j] != global__displayNormalCell){ 
                        out << theDisplay[i][j];
                    } else {
			out << theDisplay[i][j] ;
		    }
                } else {
		    out << theDisplay[i][j];

		}
            }
        }
        if (global__modded) {
            unique_ptr<Enemy> temp;
            if (i == 2) {
                out << "    Enemy Stats:";
            } else if (i == 4) {
                temp = make_unique<Tankmaster> (0, 0);
                out << "    ["<<global__displayTankmaster<<"]" << left <<
                setfill (' ') <<setw(11) << "Tankmaster";
            } else if (i == 5) {
                temp = make_unique<Vindicator> (0, 0);
                out << "    ["<<global__displayVindicator<<"]" << left <<
                    setfill (' ') <<setw(11) << "Vindicator";
            } else if (i == 6) {
                temp = make_unique<Warlock> (0, 0);
                out << "    ["<<global__displayWarlock<<"]" << left <<
                    setfill (' ') <<setw(11) << "Warlock";
            } else if (i == 7) {
                temp = make_unique<Mercenary> (0, 0);
                out << "    ["<<global__displayMercenary<<"]" << left <<
                    setfill (' ') <<setw(11) << "Mercenary";
            } else if (i == 8) {
                temp = make_unique<Defender> (0, 0, 0, 0);
                out << "    ["<<global__displayDefender<<"]" << left <<
                   setfill (' ') <<setw(11) << "Defender";
            } else if (i == 9) {
                temp = make_unique<Ninja> (0, 0);
                out << "    ["<<global__displayNinja<<"]" << left <<
                    setfill (' ') <<setw(11) << "Ninja";
            } else if (i == 10) {
                temp = make_unique<Xenosite> (0, 0);
                out << "    ["<<global__displayXenosite<<"]" << left <<
                    setfill (' ') <<setw(11) << "Xenosite";
            } else if (i == 11) {
                temp = make_unique<Wizard> (0, 0);
                out << "    ["<<global__displayWizard<<"]" << left <<
                    setfill (' ') <<setw(11) << "Wizard";
            } 
            if ((i >= 4) && (i <= 11)) {
                out << "HP:" << left << setfill(' ') << setw(3) <<
                temp->getStats("h") << "  Atk:" << left << setfill(' ')
                << setw(3) << temp->getStats("a") << "  Def:" << left <<
                setfill (' ') <<setw(3) <<temp->getStats("d");
            }
            if (i == 15){
                out << left << setfill (' ') <<setw(13) <<
                "    Enemies near you: ";
            } else if (i == 17){
                out <<elines[0];
            } else if (i == 18){
                out <<elines[1];
            } else if (i == 19){
                out <<elines[2];
            } else if (i == 20){
                out <<elines[3];
            } else if (i == 21){
                out <<elines[4];
            } else if (i == 22){
                out <<elines[5];
            } else if (i == 23){
                out <<elines[6];
            } else if (i == 24){
                out <<elines[7];
            }
            
        }
        out << endl;
    }
}






