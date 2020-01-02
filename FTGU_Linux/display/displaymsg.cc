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
            cout << "\033[1;36m" << global__moddedYes << "\033[0m" <<endl;
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
                cout <<"\033[1;32m" << "You have chosen Pleb Mode!" 
		<<"\033[0m" << endl;
                global__mode = 0;
                break;
            } else if (diff == "n") {
                cout << "\033[1;33m" <<"You have chosen Normal Mode." 
		<< "\033[0m" <<endl;
                global__mode = 1;
                break;
            } else if (diff == "b") {
                cout << "\033[1;31m" <<"You have chosen Brutal Mode!" 
		<< "\033[0m" <<endl;
                global__mode = 2;
                break;
            } else if (diff == "q") {
                hasQuit = true;
                break;
            } else if (cin) {
                cout << "\033[0;31m" <<"Invalid entry.\n" << global__modeMsg 
		<<"\033[0m";
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
                cout << "\033[1;33m"<< "You have chosen the map \"Standard\"."
 		 <<"\033[0m" << endl;
                break;
            } else if (map == "i") {
                cout << "\033[1;33m"<< "You have chosen the map \"Isolated\"."
		<<"\033[0m"<< endl;
                global__currmap = "isolated.txt";
                break;
            } else if (map == "u") {
                cout << "\033[1;33m"<< "You have chosen the map \"Crumple Zone\"."
		<<"\033[0m"<< endl;
                global__currmap = "crumpleZone.txt";
                break;
            } else if (map == "c") {
                cout << "\033[1;33m"<< "You have chosen the map \"Close Quarters\"."
		<<"\033[0m"<< endl;
                global__currmap = "closeQuarters.txt";
                break;
            } else if (map == "r") {
                cout << "\033[1;33m"<< "You have chosen the map \"Rotator\"."
		<<"\033[0m"<< endl;
                global__currmap = "rotator.txt";
                break;
            } else if (map == "q") {
                hasQuit = true;
                break;
            } else if (cin) {
                cout << "\033[0;31m" << "Invalid entry.\n" << "\033[1;35m" <<
		global__mapMsg <<"\033[0m";
            } else {
                hasQuit = true;
            }
        }
    }
}


void playerSelect(bool &hasQuit, World &theWorld) {
    // Selecting initial race
    if (global__modded) {
    cout << "\033[1;35m" << global__raceMsg1 << global__raceMsgModded
	 << endl << "\033[0m";
    } else {
	cout << global__raceMsg1 << endl;
    	cout << global__raceMsg2 << endl;
    }
    string race;
    while ((cin >> race) && (!hasQuit)) {
        if (race == global__selectMiddleman) {
            if (global__modded) cout << "\033[1;33m";
            cout <<"You have chosen to be a Middleman." << endl;
            theWorld.getPlayer(global__selectMiddleman);
	    if (global__modded) cout << "\033[0m";
            break;
        } else if (race == global__selectMannequin) {
	    if (global__modded) cout << "\033[1;33m";
            cout <<"You have chosen to be a Mannequin." << endl;
	    if (global__modded) cout << "\033[0m";
            theWorld.getPlayer(global__selectMannequin);
            break;
        } else if (race == global__selectMaddude) {
	    if (global__modded) cout << "\033[1;33m";
            cout << "You have chosen to be a Maddude." << endl;
	    if (global__modded) cout << "\033[0m";
            theWorld.getPlayer(global__selectMaddude);
            break;
        } else if (race == global__selectMeatshield) {
	    if (global__modded) cout << "\033[1;33m";
            cout <<"You have chosen to be an Meatshield." << endl;
	    if (global__modded) cout << "\033[0m";
            theWorld.getPlayer(global__selectMeatshield);
            break;
        } else if ((race ==global__selectHacker) && (global__modded)) {
            cout << "\033[1;33m"<<global__hackerIntro << "\033[0m"<<endl;
            sleep(8);
            theWorld.getPlayer(global__selectHacker);
            global__hacker = true;
            break;
        } else if (race == "q") {
            hasQuit = true;
            break;
        } else if (cin) {
            if (global__modded) cout << "\033[0;31m";
            cout << "Invalid entry."  << endl;
	    if (global__modded) cout << "\033[0m";
            if (global__modded) cout << "\033[1;35m";
            if (!global__modded) cout << global__raceMsg1 << endl
		    << global__raceMsg2 << endl;
	    else cout <<global__raceMsg1 << endl << global__raceMsgModded
		    << endl;
            if (global__modded) cout << "\033[0m";
        } else {
            hasQuit = true;
        }
    }

}

string playerInput(bool &hasQuit, bool &hasRestart, World &theWorld,
        int &currentLevel, bool &hasDied){
    // Reads in player input and calls appropriate functions
    if (global__modded) cout << "\033[1;35m";
    cout << global__doSomething << endl;
    if (global__modded) cout << "\033[0m";
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
		if (global__modded) cout << "\033[0;31m";
                if (!valid) cout << "Invalid command." << endl;
		if (global__modded) cout << "\033[0m";
            } else {
                hasQuit = true;
                return "";
            }
        } else if (com == "mod_on") {
	    global__modded = true;
	    cout << "\033[1;33mTurning on modded features...\n"<<
	        "Toggling mid-game may cause unexpected results.\n\033[1m";
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
            if (global__modded) cout << "\033[0;31m";
            if (!valid) cout << "Invalid command." << endl;
            if (global__modded) cout << "\033[0m";
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
        if (global__modded) cout << "\033[1;33m";
        if (currentLevel == 0) cout << "You have spawned." << endl;
        else cout << "You have advanced into floor " << currentLevel + 1
            << "." << endl;
        if (global__modded) cout << "\033[0m";
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
                if (global__modded) cout << "\033[1;30m";
                cout << r;
                if (global__modded) cout << "\033[0m";
                if (global__modded) cout << "\033[0;31m";
                cout << r2;
                if (global__modded) cout << "\033[0m";
                if (theWorld.playerDead()) {
                    hasDied = true;
    		    if (global__modded) cout << "\033[1;31m";
                    cout << "You died." << endl;
                    if (global__modded) cout << "\033[0m";
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
            if (global__modded) cout <<"\033[0;31m";
            cout << s;
            if (global__modded) cout <<"\033[0m";
        }
    } else {
        fstream screen{global__mapDirectory + "wingame.txt"};
    	while (screen >> noskipws >> s) {
            if (global__modded) cout <<"\033[1;33m";
            cout << s;
            if (global__modded) cout <<"\033[0m";
        }
    }
    string endgame  = theWorld.endgameCreds();
    if (global__modded) {
        if (theWorld.playerDead()) cout << "\033[0;31m"<< endgame<< "\033[0m";
	else cout << "\033[1;33m"<< endgame<< "\033[0m";
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
		    if (global__modded) cout <<"\033[0;31m";
                    cout << global__moddedInvalid << endl;
		    if (global__modded) cout <<"\033[0m";
                } else break;
            } else break;
        }
        hasQuit = true;
    }
}

ostream &operator<<(ostream &out, World &w) {
    if (global__hacker) {
        out << "\033[1;34mHACKER MAP: Stairway is"
            << " marked\033[1;31m red.\033[0m" << endl;
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
            temp << "\033[1;35m"<<"    (" << direction << ")" << left << 
                setfill(' ') << setw(9) << 
                eTypeConversion(w.enemies[i]->getDisplay())<<"\033[0m";
            try {
                temp << "\033[1;35m[\033[0m";
                for (int i = 0; i < fullbar; i++) {
                    temp << "\033[0;32m"<< "#"<<"\033[0m";
                }
                for (int i = 0; i < emptybar; i++) {
                    temp << "\033[1;31m"<< "#"<<"\033[0m";
                }
            } catch(...){
                cout << "HAX!\n";
            }
            temp <<"\033[1;35m"<< "] " << to_string(currh) << "/" 
              << to_string(maxh) << "\033[0m";
            lines[nextLine] = temp.str();
            if (nextLine < 7) nextLine++;
        }
    }
    w.td->print(w.player->gotSmartPointer(), out, lines);
    if (global__modded) out << "\033[1;35m";
    if (global__modded) out << "Enter w, a, s, d, nw, ne, sw, se to move.\n"
	<<"Enter u <direction> to use and e <direction> to attack\n\n";
    else out << "Enter no, so, we, ea, nw, ne, sw, se to move.\nEnter u "<<
        "<direction> to use and a <direction> to attack.\n\n";
    out << "Floor "<< w.levelReached + 1 << endl;
    out << "Race: " << w.player->getRace() << "   ";
    out << "Gold:" << w.player->getStat("g") << "   ";
    out << "Attack: " << w.player->getStat("a") <<"   ";
    out << "Defense: " << w.player->getStat("d") << endl;    
    if (global__modded) out << "\033[0m";
    if (!global__modded){
        out << "HP: " << w.player->getStat("h") << endl;
    } else {
        out << "\033[1;35mHP: [\033[0m";
        int maxh = w.player->getStat("mh");
        int currh = w.player->getStat("h");
        double fullbar0 = (currh * 60) / maxh;
        int fullbar = fullbar0;
        int emptybar = 60 - fullbar;
        for (int i = 0; i < fullbar; i++) {
            out << "\033[0;32m"<< "#"<<"\033[0m";
        }
        for (int i = 0; i < emptybar; i++) {
            out << "\033[1;31m"<< "#"<<"\033[0m";
        }
        out <<"\033[1;35m"<< "] " << to_string(currh) << "/" 
              << to_string(maxh) << "\033[0m";
        out << endl;
    }
    if (global__modded) out << "\033[1;35m";
    out << "Action(s): \n";
    if (global__modded) out << "\033[0m";
    return out;
}

void simulateModDL() {
    cout << "Downloading mods...\n";
    sleep(2);
    cout<< "Download complete!\n\n";
    cout<< "\033[1;35m" << global__moddedIntro<< "\033[0m";
}




