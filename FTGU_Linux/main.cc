#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <zconf.h>
#include "world.h"
#include "display/displaymsg.h"
#include "globalSettings.h"
using namespace std;


int main(int argc, char *argv[]) {
    if (argc == 1  ) {
        bool hasQuit = false;
        // Main loop, 1 iteration = 1 game (each game has several levels)
        while (!hasQuit) {
            // Opening screen
            fstream opScreen{global__mapDirectory + "opScreen.txt"};
            char s;
            while (opScreen >> noskipws >> s) {
                if (global__modded) cout << "\033[0;31m";
                cout << s;
                if (global__modded) cout << "\033[0m";
            }
            if (cin.eof()) hasQuit = true;
            cout << "Welcome to From The Ground Up: a Text-based RPG Game.\n";

            // Game indicator flags
            bool hasRestart = false; //goes back to beginning
            bool hasDied = false;
            int currentLevel = 0;
            if (cin.eof()) hasQuit = true;
            // Checking whether player wants bonus
            checkBonus(global__modded, hasQuit);
            if (global__modded) {
                simulateModDL();

            }
            if (cin.eof()) hasQuit = true;

            if (global__modded) bonusSelect(hasQuit);
            World theWorld{global__totalLevels};
            if (!hasQuit) playerSelect(hasQuit, theWorld);
            if (cin.eof()) hasQuit = true;
            if (!hasQuit) {
                // Initializing world class
                vector<string> maps = {};
                worldCycle(hasQuit, hasRestart, theWorld,
                           global__totalLevels, currentLevel, hasDied, maps);
            }
            if (hasRestart) {
                global__multiplier = 1;
                global__modded = false;
                global__mode = 1;
                global__hacker = false;
                global__currmap = "standard.txt";
            }
            //Printing endgame screen and asking to play again
            if ((!hasQuit) && (!hasRestart)) {
                ending(theWorld, hasRestart, hasQuit);
            } else if (hasRestart) {
                if (global__modded) cout << "\033[1;35m";
                cout << global__restartMsg << endl;
                if (global__modded) cout << "\033[0m";
            } else {
                if (global__modded) cout << "\033[0;31m";
                cout << global__quitMsg << endl;
                if (global__modded) cout << "\033[0m";
            }
        }
    } else {
        cout << "Incorrect arguments.\nEnter no argument for random"<<
             " map generation,\nand 1 argument specifying the map directory"<<
             " for pre-made maps.\n";
        return 1;
    }
}





