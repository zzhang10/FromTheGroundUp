#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <memory>
#include <algorithm>
#include <iomanip>
#include "world.h"
#include "display/cell.h"
#include "display/textdisplay.h"
#include "player/middleman.h"
#include "player/maddude.h"
#include "player/meatshield.h"
#include "player/mannequin.h"
#include "player/hacker.h"
#include "item/item.h"
#include "enemy/enemy.h"
#include "enemy/warlock.h"
#include "enemy/vindicator.h"
#include "enemy/mercenary.h"
#include "enemy/ninja.h"
#include "enemy/defender.h"
#include "enemy/wizard.h"
#include "enemy/xenosite.h"
#include "enemy/tankmaster.h"
#include "display/displaymsg.h"
#include "globalSettings.h"

using namespace std;



World :: World(int totalLevels) : quit{false}, mapWidth{0}, mapHeight{0},
chamberCount{1},levelReached{0}, stairx{0}, stairy{0}, enemyCount{20}{

    //Mercenaries are default to not hostile. Change this if you would like them
    //to default to hostile
    mercenaryHostile = false;

    //The default player class is Middleman
    player = make_unique<Middleman>();

    //Randomizing seed for enemy/item generation
    srand(time(nullptr));

    //Find a random level to spawn the ForceShield
    FSAppearsAt = (rand() % totalLevels);

    //Reading in map
    readMap();

}

void World::readMap() {

    //Resetting previous map, if any
    worldMap.clear();
    mapWidth = 0; mapHeight = 0;
    fstream map;

    //Reading in a map from specified directory.
    //IMPORTANT: maps must be rectangular with exactly 1 newline after the last line!
    map.open(global__mapDirectory + global__currmap);
    string tempstr;
    while (getline(map, tempstr)) {
        mapHeight ++;
        if (mapWidth == 0) mapWidth = tempstr.length();
    }
    map.close();

    //Parsing map into a TextDisplay class for the World to use.
    td = make_shared<TextDisplay>(mapWidth,mapHeight);
    map.open(global__mapDirectory + global__currmap);
    char cellChar;
    for (int i = 0; i < mapHeight; i++) {
        vector <Cell> temp;
        for (int j = 0; j < mapWidth; j++) {
            map >> noskipws >> cellChar;
            bool canWalk = false;
            for (size_t i = 0; i < global__walkableChar.size(); i++) {
                if (global__walkableChar[i] == cellChar) canWalk = true;
            }
            temp.emplace_back(Cell {i,j,0,canWalk,cellChar});
            temp.back().attach(td);
            temp.back().notifyObservers();
        }
        map >> noskipws >> cellChar; // gets rid of the /n at the end
        worldMap.emplace_back(temp);
    }
    map.close();

    //Counting the number of chambers in the map through recursion. This will
    //be used when enemies/items are generated since they are equally likely to
    //generate in each chamber regardless of chamber size.
    for (int i = 0; i < mapHeight; i++) {
        for(int j = 0; j < mapWidth; j++) {
            if ((worldMap[i][j].getDisplay() == global__displayNormalCell) &&
                (worldMap[i][j].chamberNumber == 0)){
                markRoom(worldMap[i][j], chamberCount);
                chamberCount++;
            }
        }
    }
    chamberCount--;
}

void World::markRoom(Cell &cell, int chamber) {
    if ((cell.getDisplay() == global__displayNormalCell) &&
        (cell.chamberNumber == 0)) {
        int x, y;
        cell.getPos(x, y);
        cell.chamberNumber = chamber;
        markRoom(worldMap[y][x-1], chamber);
        markRoom(worldMap[y][x+1], chamber);
        markRoom(worldMap[y-1][x], chamber);
        markRoom(worldMap[y+1][x], chamber);
        markRoom(worldMap[y-1][x-1], chamber);
        markRoom(worldMap[y+1][x-1], chamber);
        markRoom(worldMap[y-1][x+1], chamber);
        markRoom(worldMap[y+1][x+1], chamber);
    }
}

void World::getPlayer(string type) {
    //Middleman is default, and will be generated with the World class
    if (type == global__selectMaddude) player = make_unique<Maddude>();
    else if (type == global__selectMeatshield) player = make_unique<Meatshield>();
    else if (type == global__selectMannequin) player = make_unique<Mannequin>();
    else if (type == global__selectHacker) player = make_unique<Hacker>();
    player->attach(td);
}



void World::getLevel(int currentLevel) {
    //Mercenaries become peaceful at the beginning of each level. Comment out
    //next line if you would like mercenaries to always be hostile once triggered
    mercenaryHostile = false;

    //Brutal difficulty multiplier
    if (global__mode == 2 && (currentLevel > 0)) {
        enemyCount *= 1.2;
    }

    //Restore player's atk and def that might have been changed by potions
    player->restoreAtkDef();

    //Resetting enemies and items, player location and stair location randomly
    levelReached = currentLevel;
    items.clear();
    enemies.clear();
    int playerchamber = rand() % chamberCount + 1;
    int stairchamber = rand() % chamberCount + 1;
    while (stairchamber == playerchamber) {
        stairchamber = rand() % chamberCount + 1;
    }
    int xc, yc;
    randomLocation(xc, yc, playerchamber);
    player->setPos(xc, yc);
    randomLocation(stairx, stairy, stairchamber);
    worldMap[stairy][stairx].setDisplay(global__displayStair);
    randomPotion(10);
    int numOfDefenders = randomGold(10);
    if (currentLevel == FSAppearsAt) {
        int xc, yc;
        randomLocation(xc, yc);
        defenderProtected("FS", xc, yc);
        numOfDefenders++;
    }
    randomEnemy(enemyCount - numOfDefenders);
    this->update();

    //Assigning a certain enemy to be the smartPointer carrier
    int smartPointerBearer;
    do {
        smartPointerBearer = rand() % enemies.size();
    } while ((enemies[smartPointerBearer]->getDisplay() == global__displayMercenary) ||
            (enemies[smartPointerBearer]->getDisplay() == global__displayWizard));
    enemies[smartPointerBearer]->giveSmartPointer();
}

void World::update() {
    //Resets where player can go
    for (int i = 0; i < mapHeight; i++) {
        for(int j = 0; j < mapWidth; j++) {
            worldMap[i][j].notifyObservers();
            if (worldMap[i][j].getDisplay() == global__displayNormalCell) {
                worldMap[i][j].setSteppable(true);
            }
        }
    }
    int xc, yc;
    player->notifyObservers();
    for(size_t i = 0; i < items.size(); i++) {
        items[i]->notifyObservers();
        items[i]->getPos(xc, yc);

        //Cells containing potions are not steppable
        if (items[i]->getDisplay() == global__displayPotion) {
            worldMap[yc][xc].setSteppable(false);
        }

        //DefenderStashs with a valid defender will not be steppable
        if ((get<0>(items[i]->getInfo()) == "DefendedStash") ||
            (items[i]->getDisplay() == global__displayForceShield)) {
            int px, py, dx, dy;
            items[i]->getDefPos(px, py);
            bool foundProtector = false;
            for (size_t i = 0; i < enemies.size(); i++) {
                if (enemies[i]->getDisplay() == global__displayDefender) {
                    enemies[i]->getPos(dx, dy);
                    if ((px == dx) && (py == dy)) foundProtector = true;
                }
            }
            if (!foundProtector) {
                worldMap[py][px].setSteppable(true);
                items[i]->setProtect(false);
            }
        }
    }
    bool temp = true;
    checkDefender(temp);
    for(size_t i = 0; i < enemies.size(); i++) {
        enemies[i]->notifyObservers();
        enemies[i]->getPos(xc, yc);
        worldMap[yc][xc].setSteppable(false);
    }
    if (global__hacker) player->notifyObservers();
}

void World::randomLocation(int &x, int &y, int chamber) {
    int iterations = 0;
    //-1 means any valid location in the world
    int ty =  rand() % mapHeight;
    int tx = rand() % mapWidth;
    if (chamber == -1) {
        while (!validSpawn(tx, ty)){
            iterations ++;
	    if (iterations > 1000000) throw noSpaceError{};
            ty =  rand() % mapHeight;
            tx = rand() % mapWidth;
        }
    } else if (1 <= chamber) {
        while ((worldMap[ty][tx].chamberNumber != chamber) ||
               (!validSpawn(tx, ty))){
            iterations ++;
	    if (iterations > 1000000) throw noSpaceError{};
            ty =  rand() % mapHeight;
            tx = rand() % mapWidth;
        }
    }
    x = tx;
    y = ty;
}

bool World::validSpawn(int x, int y) {
    //Determines whether a cell is a valid spawn location for a player, item
    //or enemy
    if (worldMap[y][x].getDisplay() != global__displayNormalCell) return false;
    int xc, yc;
    player->getPos(xc, yc);
    if ((x == xc) && (y == yc)) return false;
    if ((x == stairx) && (y == stairy)) return false;
    for (size_t i = 0 ; i < items.size(); i++) {
        items[i]->getPos(xc, yc);
        if ((x == xc) && (y == yc)) return false;
    }
    for (size_t i = 0 ; i < enemies.size(); i++) {
        enemies[i]->getPos(xc, yc);
        if ((x == xc) && (y == yc)) return false;
    }
    return true;
}

void World::randomEnemy(int n) {
    int iterations = 0;
    for (int i = 0; i < n; i++) {
        iterations ++;
	if (iterations > 1000000) throw noSpaceError{};
        int xc, yc;
	int chamber = rand()% chamberCount + 1;
        randomLocation(xc, yc, chamber);
        //Enemies generate in uneven distribution
        int enemyId = rand() % 34;
        shared_ptr<Enemy> temp;
        if ((0 <= enemyId) && (enemyId <= 4)) {
            temp = make_shared<Warlock> (yc, xc);
        } else if ((5 <= enemyId) && (enemyId <= 10)) {
            temp = make_shared<Vindicator> (yc, xc);
        } else if ((11 <= enemyId) && (enemyId <= 18)) {
            temp = make_shared<Ninja> (yc, xc);
        } else if ((19 <= enemyId) && (enemyId <= 23)) {
            temp = make_shared<Tankmaster> (yc, xc);
        } else if ((24 <= enemyId) && (enemyId <= 29)) {
            temp = make_shared<Xenosite> (yc, xc);
        } else if ((30 <= enemyId) && (enemyId <= 33)) {
            temp = make_shared<Mercenary> (yc, xc);
            if ((mercenaryHostile) || (global__hacker)) {
                temp->setStats("isHostile", true);
            }
        }
        enemies.emplace_back(temp);
        enemies.back()->attach(td);
    }
    //Add 3 wizards to the enemy list for bonus
    if (global__modded) {
        for (int i = 0; i < 3; i++) {
	    iterations ++;
	    if (iterations > 1000000) throw noSpaceError{};
            int xc, yc;
            randomLocation(xc, yc);
            shared_ptr<Enemy> temp = make_shared<Wizard> (yc, xc);
            enemies.emplace_back(temp);
            enemies.back()->attach(td);
        }
    }
}

void World::randomPotion(int n) {
    //Generates random potion in the world
    int iterations = 0;
    for (int i = 0; i < n; i++) {
        iterations++;
        if (iterations > 1000000) throw noSpaceError{};
        int xc, yc;
        randomLocation(xc, yc, (rand() % chamberCount + 1));
        shared_ptr<Item> temp = make_shared<Potion> (yc, xc);
        items.emplace_back(temp);
        items.back()->attach(td);
    }
}

int World::randomGold(int n) {
    int numOfDefenders = 0;
    int iterations = 0;
    for (int i = 0; i < n; i++) {
        iterations++;
        if (iterations > 1000000) throw noSpaceError{};
        int xc, yc;
        randomLocation(xc, yc, (rand() % chamberCount + 1));
        //Gold generates in uneven distribution
        int goldId = rand() % 5;
        if ((0 <= goldId) && (goldId <= 2)) {
            shared_ptr<Item> temp =
                    make_shared<Gold> (yc, xc,"Normal",make_pair(0,0));
            items.emplace_back(temp);
            items.back()->attach(td);
        } else if ((3 <= goldId) && (goldId <= 4)) {
            shared_ptr<Item> temp =
                    make_shared<Gold> (yc, xc,"SmallStash",make_pair(0,0));
            items.emplace_back(temp);
            items.back()->attach(td);
        } else if (goldId == 5) {
            defenderProtected("DefendedStash", xc, yc);
            numOfDefenders++;
        }
    }
    return numOfDefenders;
}

bool World::playerDead() {
    return(player->getStat("h") <= 0);
}

void World::defenderProtected(string type, int x, int y) {
    //Generates an item defended by a Defender
    int defy = y;
    int defx = x;
    int defy0 = y;
    int defx0 = x;
    int iterations = 0;
    do {
        defx = defx0;
        defy = defy0;
        iterations++;
        if (iterations == 1000000) throw noSpaceError{};
        int defenderGrid = rand() % 8;
        if (defenderGrid == 0) defx++;
        if (defenderGrid == 1) defx--;
        if (defenderGrid == 2) defy++;
        if (defenderGrid == 3) defy--;
        if (defenderGrid == 4) {
            defx++; defy++;
        }
        if (defenderGrid == 5) {
            defx++; defy--;
        }
        if (defenderGrid == 6) {
            defx--; defy++;
        }
        if (defenderGrid == 7) {
            defx--; defy--;
        }
    } while (!validSpawn(defx,defy));
    shared_ptr<Item> temp;
    if (type == "FS") {
        temp = make_shared<ForceShield> (y, x, make_pair(defx,defy));
    } else if (type == "DS") {
        temp = make_shared<Gold> (y, x, "DefendedStash",make_pair(defx,defy));
    }
    items.emplace_back(temp);
    items.back()->attach(td);
    shared_ptr<Enemy> temp2 = make_shared<Defender> (defy, defx, x, y);
    enemies.emplace_back(temp2);
    enemies.back()->attach(td);
}

void readDir(int oldx, int oldy, int &x, int &y, string direction) {
    //Updates player location based on direction entered
    if (direction == global__moveN) {
        y = oldy - 1;
        x = oldx;
    }
    else if (direction == global__moveS) {
        y = oldy + 1;
        x = oldx;
    }
    else if (direction == global__moveW) {
        y = oldy;
        x = oldx - 1;
    }
    else if (direction == global__moveE) {
        y = oldy;
        x = oldx + 1;
    }
    else if (direction == global__moveNW) {
        y = oldy - 1;
        x = oldx - 1;
    } else if (direction == global__moveNE) {
        y = oldy - 1;
        x = oldx + 1;
    } else if (direction == global__moveSW) {
        y = oldy + 1;
        x = oldx - 1;
    } else if (direction == global__moveSE) {
        y = oldy + 1;
        x = oldx + 1;
    }
}

bool World::playerUse(int &xn, int &yn, string &returnmsg) {
    //Simulates player using a potion
    bool valid = false;
    for (size_t i = 0; i < items.size(); i++) {
        int xd, yd;
        items[i]->getPos(xd, yd);
        if ((xd == xn) && (yd == yn) &&
        (items[i]->getDisplay() == global__displayPotion)) {
            returnmsg = player->usePotion();
            items.erase(items.begin() + i);
            valid = true;
            break;
        }
    }
    if (!valid) {
        if (global__modded) returnmsg = global__noUseModded;
        else returnmsg = global__noUse;
        return false;
    }
    return true;
}

void World::checkDefender(bool &defendermsg) {
    //Checks whether the defender is alive for a defended item
    int xn, yn;
    player->getPos(xn, yn);
    for (size_t i = 0; i <enemies.size(); i++) {
        if (enemies[i]->getDisplay() == global__displayDefender) {
            int drx, dry;
            enemies[i]->protectingPos(drx, dry);
            int diffx = drx - xn;
            int diffy = dry - yn;
            if (diffx < 0) diffx *= -1;
            if (diffy < 0) diffy *= -1;
            if ((diffx <= 1) && (diffy <= 1)) {
            enemies[i]->setStats("isHostile", true);
                defendermsg = true;
            } else {
                enemies[i]->setStats("isHostile", false);
            }
        }
    }
}

bool World::playerMove(int &yn, int &xn, string &dir, string &returnmsg) {

    //Hackers are not restricted in where they move
    if (global__hacker) {
        string dir2;
        if (dir == global__moveS) dir2 = "South";
        else if (dir == global__moveN) dir2 = "North";
        else if (dir == global__moveW) dir2 = "West";
        else if (dir == global__moveE) dir2 = "East";
        else if (dir == global__moveSW) dir2 = "Southwest";
        else if (dir == global__moveSE) dir2 = "Southeast";
        else if (dir == global__moveNW) dir2 = "Northwest";
        else if (dir == global__moveNE) dir2 = "Northeast";
        returnmsg = global__move + dir2 ;
        bool toggled = false;

    //Check picking up item
	bool gold1 = false;
        for (size_t i = 0; i < items.size(); i++) {
            int xd, yd;
            bool era = false;
            items[i]->getPos(xd, yd);
            if ((xd == xn) && (yd == yn)) {
                if (items[i]->getDisplay() == global__displayGold) {
                    returnmsg += player->pickupGold
                            (get<0>(items[i]->getInfo()));
                    era = true;
                    gold1 = true;
                } else if (items[i]->getDisplay() == global__displayForceShield) {
                    returnmsg = global__playerUFS;
                    returnmsg += player->pickupGold("FS");
                    era = true;
                    gold1 = true;
                } else if (items[i]->getDisplay() == global__displaySmartPtr) {
                    returnmsg += player->pickupGold("C");
                    era = true;
                    gold1 = true;
                }
                if ((get<2>(items[i]->getInfo())) && 
                    (items[i]->getDisplay() != global__displayPotion)) {
                    toggled = true;
                }
            }
            if (era) items.erase(items.begin() + i);
        }
	this->update();
        if (!gold1) returnmsg+= ".\n";
        if ((yn >= 0) && (yn < mapHeight) && (xn >= 0) && (xn < mapWidth)) {
            if (!worldMap[yn][xn].isSteppable()) {
                returnmsg += global__hackerWalkOver;
            }
        } else {
            if (yn < 0) yn = mapHeight - 1;
            if (yn >= mapHeight) yn = 0;
            if (xn < 0) xn = mapWidth - 1;
            if (xn >= mapWidth) xn = 0;
            returnmsg += global__hackerMapBorder;
        }
        if (toggled) returnmsg += global__defenderHack;
        player->setPos(xn, yn);
        return true;
    }

    //Check whether they can go there
    if (worldMap[yn][xn].isSteppable()) {
        string dir2;
        if (dir == global__moveS) dir2 = "South";
        else if (dir == global__moveN) dir2 = "North";
        else if (dir == global__moveW) dir2 = "West";
        else if (dir == global__moveE) dir2 = "East";
        else if (dir == global__moveSW) dir2 = "Southwest";
        else if (dir == global__moveSE) dir2 = "Southeast";
        else if (dir == global__moveNW) dir2 = "Northwest";
        else if (dir == global__moveNE) dir2 = "Northeast";
        returnmsg = global__move + dir2;
        for (size_t i = 0; i < items.size(); i++) {
            int xd, yd;
            items[i]->getPos(xd, yd);
            if ((xd == xn) && (yd == yn)) {
                if (items[i]->getDisplay() == global__displayGold) {
                    if (get<2>(items[i]->getInfo())) {
                        if (global__modded)returnmsg = global__goldProtectedModded;
                        else returnmsg = global__goldProtected;
                        return false;
                    } else {
                        returnmsg += player->pickupGold
                                (get<0>(items[i]->getInfo()));
                        items.erase(items.begin() + i);
                        player->setPos(xn, yn);
			this->update();
                        return true;
                    }
                } else if (items[i]->getDisplay() == global__displayForceShield) {
                    if (get<2>(items[i]->getInfo())) {
                        if (global__modded) returnmsg = global__FSProtectedModded;
                        else returnmsg = global__FSProtected;
                        return false;
                    } else {
                        returnmsg = global__playerUFS;
                        returnmsg += player->pickupGold("FS");
                        items.erase(items.begin() + i);
                        player->setPos(xn, yn);
			this->update();
                        return true;
                    }
                } else if (items[i]->getDisplay() == global__displaySmartPtr) {
                    returnmsg += player->pickupGold("C");
                    items.erase(items.begin() + i);
                    player->setPos(xn, yn);
		    this->update();
                    return true;
                }
            }
        }
        bool neargold = false;
        bool nearpot = false;
        bool nearFS = false;
        bool nearDh = false;
        for (size_t i = 0; i < items.size(); i++) {
            int ix, iy, diffx, diffy;
            items[i]->getPos(ix, iy);
            diffx = (ix > xn) ? (ix - xn) : (xn - ix);
            diffy = (iy > yn) ? (iy - yn) : (yn - iy);
            if ((diffx <= 1) && (diffy <= 1)) {
                if (items[i]->getDisplay() == global__displayPotion) {
                    nearpot = true;
                } else if (items[i]->getDisplay() == global__displayGold) {
                    neargold = true;
                } else if (items[i]->getDisplay() == global__displayForceShield) {
                    nearFS = true;
                }
                if ((get<0>(items[i]->getInfo())) == "DefendedStash") nearDh = true;
            }
        }
        if (neargold && nearpot) {
            string SA = global__playerSeeAll;
            returnmsg += SA;
        } else if (nearpot) {
            string SP = global__playerSeeP;
            returnmsg += SP;
        } else if (neargold) {
            string SG = global__playerSeeG;
            returnmsg += SG;
        } else if (nearFS) {
            string SFS = global__playerSeeFS;
            returnmsg += SFS;
        }
        returnmsg += ".";
        stringstream temp{};
        temp << endl;
        returnmsg += (temp.str());
	player->setPos(xn, yn);
        bool defendermsg = false;
	checkDefender(defendermsg);
        if ((nearDh) && (defendermsg)) {
            if (global__modded) returnmsg += global__defenderMadDHModded;
            else returnmsg += global__defenderMadDH;
            returnmsg += (temp.str());
        } else if ((nearFS) && (defendermsg)) {
            if (global__modded) returnmsg += global__defenderMadFSModded;
            else returnmsg += global__defenderMadFS;
            returnmsg += (temp.str());
        }
    }  else {
        if (global__modded) {
            int msgnum = rand() % 3;
            if (msgnum == 0) returnmsg = global__noWalkModded1;
            else if (msgnum == 1) returnmsg = global__noWalkModded2;
            else if (msgnum == 2) returnmsg = global__noWalkModded3;
        } else {
            returnmsg += global__noWalk;
        }
        return false;
    }
    return true;
}

string eTypeConversion(char display) {
    if (display == global__displayVindicator) return "Vindicator";
    else if (display == global__displayWarlock) return "Warlock";
    else if (display == global__displayDefender) return "Defender";
    else if (display == global__displayXenosite) return "Xenosite";
    else if (display == global__displayNinja) return "Ninja";
    else if (display == global__displayMercenary) return "Mercenary";
    else if (display == global__displayTankmaster) return "Tankmaster";
    else if (display == global__displayWizard) return "Wizard";
    else return " ";
}

bool World::playerAttack(int &yn, int &xn, int &yc, int &xc,
        string &returnmsg) {
    bool valid = false;
    for (size_t i = 0; i < enemies.size(); i++) {
        int xd, yd;
        enemies[i]->getPos(xd, yd);
        if ((xd == xn) && (yd == yn)) {
            string name = eTypeConversion(enemies[i]->getDisplay());
            int dmgDealt = enemies[i]->getAttacked(player->getStat("a"));
            returnmsg += global__genMessage("playerAttack",name, dmgDealt);
            stringstream temp{""};
            temp << endl;
            returnmsg += temp.str();
            bool willbeDead = false;
            if (enemies[i]->getStats("h") <= 0) {
                returnmsg += global__genMessage("enemyDie",name, -1);
                if (enemies[i]->gotSmartPointer()) {
                    shared_ptr<Item> temp3 = make_shared<SmartPointer> (yd, xd);
                    items.emplace_back(temp3);
                    items.back()->attach(td);
                    returnmsg += " It dropped a SmartPointer.";
                }
                returnmsg += temp.str();
                if (enemies[i]->getDisplay() == global__displayMercenary){
                    shared_ptr<Item> temp =
                            make_shared<Gold> (yd, xd,"MercenaryStash",make_pair(0,0));
                    items.emplace_back(temp);
                    items.back()->attach(td);
                } else if (enemies[i]->getDisplay() == global__displayWizard) {
                    shared_ptr<Item> temp =
                            make_shared<Potion> (yd, xd);
                    items.emplace_back(temp);
                    items.back()->attach(td);
                } else if (enemies[i]->getDisplay() != global__displayDefender) {
                        player->pickupGold("DROP");
                }
                willbeDead = true;
            }
            if ((enemies[i]->getDisplay() == global__displayMercenary) &&
            (!(enemies[i]->getStats("isHostile")))){
	    	mercenaryHostile = true;
                for (size_t i = 0; i < enemies.size(); i++) {
                    if (enemies[i]->getDisplay() == global__displayMercenary){
                        enemies[i]->setStats("isHostile", true);
                    }
                }
                if (global__modded) returnmsg += global__mercenaryHostileModded;
                else returnmsg += global__mercenaryHostile;
                returnmsg += temp.str();
            }
            valid = true;
            if (willbeDead) enemies.erase(enemies.begin() + i);
            break;
        }
    }
    if (!valid) {
        if (global__modded)returnmsg = global__noAtkModded;
        else returnmsg = global__noAtk;
        return false;
    }
    return true;
}

bool World::playerTurn(string type, string dir, string &returnmsg) {
    //return true for valid move, false for invalid move
    returnmsg.clear();
    int xc, yc, xn, yn = 0;
    player->getPos(xc, yc);
    readDir(xc, yc, xn, yn, dir);
    //cout << "player at row "<< yc << " col "<< xc <<endl; // debug msg
    if (type == "u") {
        return playerUse(xn, yn, returnmsg);
    } else if (type =="m") {
        return playerMove(yn, xn, dir, returnmsg);
    } else if (type == "a") {
        return playerAttack(yn, xn, yc, xc, returnmsg);
    }
    return true;
}

bool operator<(shared_ptr<Enemy>e1, std::shared_ptr<Enemy>e2) {
    // Custom overloaded operator for comparing enemy positions
    int e1x, e1y, e2x, e2y;
    e1->getPos(e1x, e1y);
    e2->getPos(e2x, e2y);
    if (e1y < e2y) return true;
    else if (e1y == e2y) {
        if (e1x < e2x) return true;
        else return false;
    } else return false;
}

string World::enemyTurn(){
    stringstream returnmsg{""};
    sort (enemies.begin(), enemies.end());
    int px, py, ex, ey;
    player->getPos(px, py);
    for (size_t i = 0; i < enemies.size(); i++) {
        enemies[i]->getPos(ex, ey);
        int diffx = ex - px;
        int diffy = ey - py;
        if (diffx < 0) diffx *= -1;
        if (diffy < 0) diffy *= -1;
        if ((enemies[i]->getStats("isHostile")) && (diffx <= 1) && (diffy <= 1)) {
            // If enemy is within 1 block, they stop moving and attack
            string name = eTypeConversion(enemies[i]->getDisplay());
            int damageReceived = player->receiveAttack(enemies[i]->getStats("a"),
		(enemies[i]->getDisplay() == global__displayWizard));
            if (damageReceived == -1) {
                // -1 means enemy missed
                returnmsg << global__genMessage("enemyMiss", name, -1) << endl;
            } else {
                // enemy hit
                returnmsg << global__genMessage
                ("enemyHit", name, damageReceived) << endl;
            }
        } else if ((enemies[i]->getDisplay() != global__displayDefender) &&
		    ((!enemies[i]->getStats("isHostile")) ||(diffx > 1) ||(diffy > 1))) {
	    int iteration = 0;
            int Newx, Newy;
	    bool willmove = true;
            do {
		iteration++;
		if (iteration > 100000) {
		    // After 100000 unsuccessful tries to move enemy, it is likely that
		    // they are stuck. We break the infinite loop here.
		    willmove = false;
		    break;
		}
                enemies[i]->getPos(Newx, Newy);
                int dir = rand() % 8;
                if (dir == 0) Newx ++;
                else if (dir == 1) Newx --;
                else if (dir == 2) Newy --;
                else if (dir == 3) Newy ++;
                else if (dir == 4) {
                    Newx --; Newy++;
                } else if (dir == 5) {
                    Newx --; Newy--;
                } else if (dir == 6) {
                    Newx ++; Newy++;
                } else if (dir == 7) {
                    Newx ++; Newy--;
                }
            } while (!enemyWalkable(Newx, Newy));
	    if (willmove){
            	worldMap[ey][ex].setSteppable(true);
            	worldMap[Newy][Newx].setSteppable(false);
            	enemies[i]->setPos(Newx, Newy);
	    }
        }
    }
    return returnmsg.str();
}

bool World::enemyWalkable(int Newx, int Newy) {
    if (!worldMap[Newy][Newx].isSteppable()) return false;
    if (worldMap[Newy][Newx].getDisplay() != global__displayNormalCell) {
        return false;
    }
    for(size_t i = 0; i < items.size(); i++) {
        int xx, yy;
        items[i]->getPos(xx, yy);
        if ((xx==Newx) && (yy == Newy)) return false;
    }
    for(size_t i = 0; i < enemies.size(); i++) {
        int xx, yy;
        enemies[i]->getPos(xx, yy);
        if ((xx==Newx) && (yy == Newy)) return false;
    }
    int px, py;
    player->getPos(px, py);
    if ((px==Newx) && (py == Newy)) return false;
    return true;
}

bool World::endLevel() {
    int xc, yc;
    player->getPos(xc, yc);
    if ((xc != stairx) || (yc != stairy)) {
        return false;
    }
    worldMap[stairy][stairx].setDisplay(global__displayNormalCell);
    return true;
}

string World::endgameCreds() {
    double realscore = player->getStat("g");
    if (player->getRace() == "Middleman") realscore *= 1.5;
    stringstream temp{""};
    if (playerDead()) {
        temp << "||                                You lost!     " <<
             "                             ||" << endl;
    } else {
        temp << "||                                You Won!      " <<
             "                             ||" << endl;
    }
    temp << "||                        You have reached floor " <<
         left << setfill (' ') <<setw(28) << levelReached + 1 <<
        "||" << endl;
    temp << "||                            Your score is " <<
         left << setfill (' ') <<setw(33) <<realscore <<
        "||" << endl;
    temp << "||                                       "
            "                                    ||" << endl;
    temp << "||                                       "
            "                                    ||" << endl;
    temp << "||====================================================" <<
            "=======================||" << endl;

    return temp.str();
}

World :: ~World() {
    items.clear();
    enemies.clear();
    worldMap.clear();
    global__multiplier = 1;
    global__modded = false;
    global__mode = 1;
    global__hacker = false;
    global__currmap = "standard.txt";
}






