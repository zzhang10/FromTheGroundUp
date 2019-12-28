#include"displaymsg.h"
#include "../world.h"
#include "../enemy/enemy.h"
#include "../player/player.h"
#include <vector>
#include "../item/item.h"
#include <string>
#include <zconf.h>
#include <iomanip>
#include <fstream>
#include "../globalSettings.h"

using namespace std;

vector<string> validDir = {global__moveN, global__moveS, global__moveE,
                           global__moveW, global__moveSE, global__moveSW,
                           global__moveNE, global__moveNW};

void checkBonus(bool &bonusFeature, bool &hasQuit) {
    cout << global__moddedMsg << endl;
    string bonus;
    while (true) {
        if ((cin >> bonus) && ((bonus == "Y") || (bonus == "y"))) {
            cout << global__moddedYes <<endl;
            bonusFeature = true;
            break;
        } else if ((bonus == "Normal") || (bonus == "n")) {
            cout <<global__moddedNo << endl;
            break;
        } else if (bonus == "q") {
            hasQuit = true;
	    break;
        } else if (cin) {
            cout << global__moddedInvalid << endl;
        } else {
	    hasQuit = true;
	    return;
	    }
    }
}

void bonusSelect(bool &hasQuit){
    if ((global__modded) && (!hasQuit)){
        cout << global__modeMsg;
        string diff;
        while ((cin >> diff) && (!hasQuit)) {
            if (diff == "p") {
                cout  << "You have chosen Pleb Mode!"
		 << endl;
                global__mode = 0;
                break;
            } else if (diff == "n") {
                cout <<"You have chosen Normal Mode."
		<<endl;
                global__mode = 1;
                break;
            } else if (diff == "b") {
                cout <<"You have chosen Brutal Mode!"
		<<endl;
                global__mode = 2;
                break;
            } else if (diff == "q") {
                hasQuit = true;
                break;
            } else if (cin) {
                cout <<"Invalid entry.\n" << global__modeMsg
		;
            } else {
                hasQuit = true;
            }
        }
    }
    if ((global__modded) && (!hasQuit)){
        cout << global__mapMsg ;
        string map;
        while ((cin >> map) && (!hasQuit)) {
            if (map == "s") {
                cout << "You have chosen the map \"Standard\"."
 		  << endl;
                break;
            } else if (map == "i") {
                cout << "You have chosen the map \"Isolated\"."
		<< endl;
                global__currmap = "isolated.txt";
                break;
            } else if (map == "u") {
                cout << "You have chosen the map \"Crumple Zone\"."
		<< endl;
                global__currmap = "crumpleZone.txt";
                break;
            } else if (map == "c") {
                cout << "You have chosen the map \"Close Quarters\"."
		<< endl;
                global__currmap = "closeQuarters.txt";
                break;
            } else if (map == "r") {
                cout << "You have chosen the map \"Rotator\"."
		<< endl;
                global__currmap = "rotator.txt";
                break;
            } else if (map == "q") {
                hasQuit = true;
                break;
            } else if (cin) {
                cout << "Invalid entry.\n" <<
		global__mapMsg ;
            } else {
                hasQuit = true;
            }
        }
    }
}


void playerSelect(bool &hasQuit, World &theWorld) {
    // Selecting initial race
    if (global__modded) {
    cout << global__raceMsg1 << global__raceMsgModded
	 << endl ;
    } else {
	cout << global__raceMsg1 << endl;
    	cout << global__raceMsg2 << endl;
    }
    string race;
    while ((cin >> race) && (!hasQuit)) {
        if (race == global__selectMiddleman) {
            cout <<"You have chosen to be a Middleman." << endl;
            theWorld.getPlayer(global__selectMiddleman);
            break;
        } else if (race == global__selectMannequin) {
            cout <<"You have chosen to be a Mannequin." << endl;
            theWorld.getPlayer(global__selectMannequin);
            break;
        } else if (race == global__selectMaddude) {
            cout << "You have chosen to be a Maddude." << endl;
            theWorld.getPlayer(global__selectMaddude);
            break;
        } else if (race == global__selectMeatshield) {
            cout <<"You have chosen to be an Meatshield." << endl;
            theWorld.getPlayer(global__selectMeatshield);
            break;
        } else if ((race ==global__selectHacker) && (global__modded)) {
            cout <<global__hackerIntro <<endl;
            sleep(8);
            theWorld.getPlayer(global__selectHacker);
            global__hacker = true;
            break;
        } else if (race == "q") {
            hasQuit = true;
            break;
        } else if (cin) {
            cout << "Invalid entry."  << endl;
            if (!global__modded) cout << global__raceMsg1 << endl
		    << global__raceMsg2 << endl;
	    else cout <<global__raceMsg1 << endl << global__raceMsgModded << endl;

        } else {
            hasQuit = true;
        }
    }

}

string playerInput(bool &hasQuit, bool &hasRestart, World &theWorld,
        int &currentLevel, bool &hasDied){
    // Reads in player input and calls appropriate functions
    cout << global__doSomething << endl;
    string com, com2;
    bool playerDone = false;
    string r = "";
    while ((!playerDone) && (cin >> com)) {
        if ((cin.eof()) || (com == "q")) {
            hasQuit = true;
            return "";
        } else if (com == "r") {
            hasRestart = true;
            currentLevel = 0;
            return "";
        } else if ((com == "u") || ((!global__modded) && (com == "a")) ||
		   (global__modded && (com == "e"))) {//potion or attack
	    if (com == "e") com = "a";
            string dir2;
            if (cin >> dir2) {
                bool valid = false;
		if (global__modded) {
		    // Changing wasd commands to directions
                    if (dir2 == "w") dir2 = global__moveN;
		    else if (dir2 == "a") dir2 = global__moveW;
		    else if (dir2 == "s") dir2 = global__moveS;
		    else if (dir2 == "d") dir2 = global__moveE;
		    else if (dir2 == global__moveW) dir2 = "__";
		    else if (dir2 == global__moveE) dir2 = "__";
		    else if (dir2 == global__moveS) dir2 = "__";
	      	    else if (dir2 == global__moveN) dir2 = "__";

		}
                for (size_t i = 0; i < validDir.size(); ++i) {
                    if (dir2 == validDir[i]) {
                        playerDone = theWorld.playerTurn(com, dir2, r);
                        if (!playerDone) cout << r << endl;
                        valid = true;
                        break;
                    }
                }
                if (theWorld.playerDead()) {
                    hasDied = true;
                    return "";
                }
                if (!valid) cout << "Invalid command." << endl;
            } else {
                hasQuit = true;
                return "";
            }
        } else if (com == "mod_on") {
	    global__modded = true;
	    cout << "Turning on modded features...\n"<<
	        "Toggling mid-game may cause unexpected results.\n";
	    sleep(1);
	    cout << theWorld;
        } else if (com == "mod_off") {
            global__modded = false;
	    cout << "Turning off modded features...\n"<<
	        "Toggling mid-game may cause unexpected results.\n";
            sleep(1);
	    cout << theWorld;
        } else {
            bool valid = false;
	    if (global__modded) {
                if (com == "w") com = global__moveN;
		else if (com == "a") com = global__moveW;
		else if (com == "s") com = global__moveS;
		else if (com == "d") com = global__moveE;
		else if (com == global__moveW) com = "__";
		else if (com == global__moveE) com = "__";
		else if (com == global__moveS) com = "__";
		else if (com == global__moveN) com = "__";
	    }
            for (size_t i = 0; i < validDir.size(); ++i) {
                if (com == validDir[i]) {
                    playerDone = theWorld.playerTurn("m", com, r);
                    if (!playerDone) cout << r << endl;
                    valid = true;
                    break;
                }
            }
            if (!valid) cout << "Invalid command." << endl;
        }
        theWorld.update();
    }
    return r;
}


void worldCycle(bool &hasQuit, bool &hasRestart,World &theWorld,
                const int &totalLevels, int &currentLevel, bool &hasDied,
                vector<string>&maps) {
    while ((currentLevel < totalLevels) && (!hasQuit) && (!hasRestart)) {
        try {
            theWorld.getLevel(currentLevel);

        } catch (noSpaceError&) {
            cout << global__failedGen << endl;
            continue;
        }
        cout << theWorld;
        if (currentLevel == 0) cout << "You have spawned." << endl;
        else cout << "You have advanced into floor " << currentLevel + 1
            << "." << endl;
        while ((!theWorld.endLevel()) && (!hasQuit) && (!hasRestart)) {
            //P layer input is here
            string r = playerInput(hasQuit, hasRestart, theWorld,
                                   currentLevel, hasDied);
            if (hasDied) {
                cout << r;
                return;
            }
            if (cin.eof()) {
                hasQuit = true;
                return;
            }
            if (theWorld.endLevel()) break;
            if ((!hasQuit) && (!hasRestart) && (!theWorld.endLevel())) {
                string r2 = theWorld.enemyTurn();
                theWorld.update();
                cout << theWorld;
                cout << r;
                cout << r2;
                if (theWorld.playerDead()) {
                    hasDied = true;
                    cout << "You died." << endl;
                    return;
                }
            }
        }
        currentLevel++;
        if (global__mode == 2) global__multiplier *= 1.1;
    }
}

void ending(World &theWorld, bool &hasRestart, bool &hasQuit){  
    char s;
    if(theWorld.playerDead()) {
        fstream screen{global__mapDirectory + "endgame.txt"};
    	while (screen >> noskipws >> s) {
            cout << s;
        }
    } else {
        fstream screen{global__mapDirectory + "wingame.txt"};
    	while (screen >> noskipws >> s) {
            cout << s;
        }
    }
    string endgame  = theWorld.endgameCreds();
    if (global__modded) {
        if (theWorld.playerDead()) cout << endgame;
	else cout << endgame;
    } else {
       cout << endgame;
    }
    if (!hasRestart) {
        cout << global__replayMsg << endl;
        string choice;
        while (true) {
            if (cin >> choice) {
                if ((choice == "Y") || (choice == "y")) {
                    return;
                } else if ((choice != "Normal") && (choice != "n")) {
                    cout << global__moddedInvalid << endl;
                } else break;
            } else break;
        }
        hasQuit = true;
    }
}

ostream &operator<<(ostream &out, World &w) {
    if (global__hacker) {
        out << "HACKER MAP: Stairway is"
            << " marked red." << endl;
    }
    vector<string> lines = {"", "", "", "", "","","",""};
    int nextLine = 0; 
    for (size_t i = 0; i < w.enemies.size(); i++) {        
        int px, py, ex, ey;
        w.player->getPos(px, py);
        w.enemies[i]->getPos(ex, ey);
        int diffx = ex - px;
        int diffy = ey - py;
        if (diffx < 0) diffx *= -1;
        if (diffy < 0) diffy *= -1;
        if ((diffx <= 1) && (diffy <= 1)) {
            int maxh = w.enemies[i]->getStats("mh");
            int currh = w.enemies[i]->getStats("h");
            double fullbar0 = (currh * 25) / maxh;
            int fullbar = fullbar0;
	    if (fullbar == 0) fullbar = 1;
            int emptybar = 25 - fullbar;
            string direction = " ";
            if ((px == ex) && (py == ey + 1)) direction = "NO";
            else if ((px == ex) && (py == ey - 1)) direction = "SO";
            else if ((px == ex - 1) && (py == ey)) direction = "EA";
            else if ((px == ex + 1) && (py == ey)) direction = "WE";
            else if ((px == ex + 1) && (py == ey + 1)) direction = "NW";
            else if ((px == ex - 1) && (py == ey + 1)) direction = "NE";
            else if ((px == ex + 1) && (py == ey - 1)) direction = "SW";
            else if ((px == ex - 1) && (py == ey - 1)) direction = "SE";
            stringstream temp{" "};
            temp <<"    (" << direction << ")" << left <<
                setfill(' ') << setw(9) << 
                eTypeConversion(w.enemies[i]->getDisplay());
            try {
                temp << "[";
                for (int i = 0; i < fullbar; i++) {
                    temp << "#";
                }
                for (int i = 0; i < emptybar; i++) {
                    temp << ".";
                }
            } catch(...){
                cout << "HAX!\n";
            }
            temp << "] " << to_string(currh) << "/"
              << to_string(maxh) ;
            lines[nextLine] = temp.str();
            if (nextLine < 7) nextLine++;
        }
    }
    w.td->print(w.player->gotSmartPointer(), out, lines);
    if (global__modded) out << "Enter w, a, s, d, nw, ne, sw, se to move.\n"
	<<"Enter u <direction> to use and e <direction> to attack\n\n";
    else out << "Enter no, so, we, ea, nw, ne, sw, se to move.\nEnter u "<<
        "<direction> to use and a <direction> to attack.\n\n";
    out << "Floor "<< w.levelReached + 1 << endl;
    out << "Race: " << w.player->getRace() << "   ";
    out << "Gold:" << w.player->getStat("g") << "   ";
    out << "Attack: " << w.player->getStat("a") <<"   ";
    out << "Defense: " << w.player->getStat("d") << endl;
    if (!global__modded){
        out << "HP: " << w.player->getStat("h") << endl;
    } else {
        out << "HP: [";
        int maxh = w.player->getStat("mh");
        int currh = w.player->getStat("h");
        double fullbar0 = (currh * 60) / maxh;
        int fullbar = fullbar0;
        int emptybar = 60 - fullbar;
        for (int i = 0; i < fullbar; i++) {
            out << "#";
        }
        for (int i = 0; i < emptybar; i++) {
            out << ".";
        }
        out << "] " << to_string(currh) << "/"
              << to_string(maxh) ;
        out << endl;
    }
    out << "Action(s): \n";
    return out;
}

void simulateModDL() {
    cout << "Downloading mods...\n";
    sleep(2);
    cout<< "Download complete!\n\n";
    cout<< global__moddedIntro;
}




