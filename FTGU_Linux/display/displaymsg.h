#ifndef DISPLAYMSG_H
#define DISPLAYMSG_H
#include <iostream>
#include <vector>
#include "../observer.h"
#include "../world.h"
#include <sstream>


//Operates the section of the game that prompt the player for bonus features
void checkBonus(bool &bonusFeature, bool &hasQuit);

//Operates player selection
void playerSelect(bool &hasQuit, World &theWorld);

//Operates 1 game. 1 game can have many levels
void worldCycle(bool &hasQuit, bool &hasRestart, World &theWorld,
        const int &totalLevels, int &currentLevel, bool &hasDied,
        std::vector<std::string>&maps);

//Operates when the game (not the level) has ended
void ending(World &theWorld, bool &hasRestart, bool &hasQuit);

//Outputs the world to the desired stream
std::ostream &operator<<(std::ostream &out, World &w);

//bonus feature selection
void bonusSelect(bool &hasquit);

//Simulates Mod downloads
void simulateModDL();




#endif


