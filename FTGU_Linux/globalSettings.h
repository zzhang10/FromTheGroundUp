#ifndef GLOBALSETTINGS_H
#define GLOBALSETTINGS_H

#include <string>
#include <vector>

//-----------------------------NORMAL GAMEPLAY-------------------------------

//Total number of levels per game
extern const int global__totalLevels;

//The directory where maps are stored
extern const std::string global__mapDirectory;

//The map that player will play in
extern std::string global__currmap;

//Characters that player can walk on
extern const std::vector<char>global__walkableChar;

//Message prompting player to enter a command
extern const std::string global__doSomething;

//Message for choosing race
extern const std::string global__raceMsg1;
extern const std::string global__raceMsg2;

//Message when player moves
extern const std::string global__move;

//Message on restart
extern const std::string global__restartMsg;

//Message at endgame asking for replay
extern const std::string global__replayMsg;

//Message on quit
extern const std::string global__quitMsg;

//Message when player is near a defender protected item
extern const std::string global__defenderMadDH;
extern const std::string global__defenderMadFS;

//Message when the player is near gold, Force Shield, Potion, or multiple items
extern const std::string global__playerSeeG;
extern const std::string global__playerSeeFS;
extern const std::string global__playerSeeP;
extern const std::string global__playerSeeAll;

//Message when player tries to take a protected defender horde
extern const std::string global__goldProtected;

//Message when player tries to take a protected forceshield
extern const std::string global__FSProtected;

//Message when player cannot walk/use/attack that direction
extern const std::string global__noWalk;
extern const std::string global__noUse;
extern const std::string global__noAtk;

//Message when player takes the forceshield
extern const std::string global__playerUFS;

//Message when Mercenary turns hostile
extern const std::string global__mercenaryHostile;

//Message when too many items are generated in a single room:
extern const std::string global__failedGen;

//Display characters for enemies and special cells
extern const char global__displayPotion;
extern const char global__displayGold;
extern const char global__displayForceShield ;
extern const char global__displayDefender;
extern const char global__displayWarlock;
extern const char global__displayXenosite;
extern const char global__displayVindicator;
extern const char global__displayNinja;
extern const char global__displayMercenary;
extern const char global__displayTankmaster;
extern const char global__displaySmartPtr;
extern const char global__displayNormalCell;
extern const char global__displayPlayer;
extern const char global__displayStair;

//Commands to select corresponding races
extern const std::string global__selectMiddleman;
extern const std::string global__selectMannequin;
extern const std::string global__selectMeatshield;
extern const std::string global__selectMaddude;

//Movement commands
extern const std::string global__moveS;
extern const std::string global__moveN;
extern const std::string global__moveW;
extern const std::string global__moveE;
extern const std::string global__moveSW;
extern const std::string global__moveSE;
extern const std::string global__moveNW;
extern const std::string global__moveNE;



//------------------------------MODDED GAMEPLAY-------------------------------

//Message asking if player wants to add mods
extern const std::string global__moddedMsg;

//Message when player accepts mods/declines mods/enters invalid command
extern const std::string global__moddedYes;
extern const std::string global__moddedNo;
extern const std::string global__moddedInvalid;

//True for modded contents, and False for default contents
extern bool global__modded;

//0 == Pleb mode, 1 == normal mode, 2 == brutal mode. Only effective when
//global__modded is True
extern int global__mode;

//Multiplier for enemy health and atk. Works only if global__mode == 2
extern double global__multiplier;

//Modded intro
extern const std::string global__moddedIntro;

//Modded race selection message
extern const std::string global__raceMsgModded;

//Mode selection message
extern const std::string global__modeMsg;

//Map selection message
extern const std::string global__mapMsg;

//Message when player tries to take protected items
extern const std::string global__goldProtectedModded;
extern const std::string global__FSProtectedModded;

//Message when player cannot walk/use/attack in that direction
extern const std::string global__noWalkModded1 ;
extern const std::string global__noWalkModded2;
extern const std::string global__noWalkModded3;
extern const std::string global__noUseModded;
extern const std::string global__noAtkModded;

//Message when Mercenary becomes hostile
extern const std::string global__mercenaryHostileModded;

//Message when player is near a defender protected item
extern const std::string global__defenderMadDHModded;
extern const std::string global__defenderMadFSModded;

//Generates a random message for certain events
const std::string global__genMessage
        (std::string type, std::string name, int amount);

//Display character for a Wizard
extern const char global__displayWizard;

//True for hacker mode
extern bool global__hacker;

//Intro message to explain the hacker race
extern const std::string global__hackerIntro;

//Message when hacker walks over a normally unwalkable cell
extern const std::string global__hackerWalkOver;

//Message when hacker walks around the map by walking off the edge
extern const std::string global__hackerMapBorder;

//Message when hacker takes a defended item
extern const std::string global__defenderHack;

//Command to select hacker mode
extern const std::string global__selectHacker;

#endif




