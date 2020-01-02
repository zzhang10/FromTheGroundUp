#ifndef WORLD_H
#define WORLD_H
#include <iostream>
#include <utility>
#include <vector>
#include <memory>
#include "display/cell.h"

class Subject;
class TextDisplay;
class Player;
class Item;
class Enemy;

//The noSpaceError class is thrown when there are too many entities trying to
// generate in too small of a room.
class noSpaceError{};


class World {
    //The World class is the central class of the entire game of FTGU.

    //Whether player has quit
    bool quit;

    //Whether mercenaries are hostile
    bool mercenaryHostile;

    //Level where Force Shield appears
    int FSAppearsAt;

    //Map size
    int mapWidth, mapHeight;

    //Number of separated chambers
    int chamberCount;

    //Player's current level
    int levelReached;

    //Location of the stair
    int stairx, stairy;

    //Enemy count
    int enemyCount;

    //2D vector of cells, keeping track of the map
    std::vector <std::vector <Cell>> worldMap;

    //Potions, Gold, Force Shield, SmartPointer
    std::vector<std::shared_ptr<Item>> items;

    //All enemies
    std::vector<std::shared_ptr<Enemy>> enemies;

    //The player
    std::unique_ptr<Player> player;

    //The observer, a TextDisplay
    std::shared_ptr<Observer> td;

    //Generates n random potions
    void randomPotion(int n);

    //Generates n enemies
    void randomEnemy(int n);

    //Generates n random gold piles, returns number of Defenders(Stashs)
    int randomGold(int n);

    //Generates a defender protected item (DH or G)
    void defenderProtected(std::string type, int x, int y);

    //Sets x and y to a valid location according to the chamber number. Chamber
    // must be either -1 or [1, chamberCount]. -1 means any chamber.
    void randomLocation(int &x, int &y, int chamber = -1);

    //Marks rooms by chamber number after the map is parsed.
    void markRoom(Cell &cell, int chamber);

    //Returns true if something can spawn at row y, col x. False otherwise
    bool validSpawn(int x, int y);

    //Simulates player using/moving/attacking, returns true if that action is
    //valid/successful, and false otherwise.
    bool playerUse(int &, int &, std::string &);
    bool playerMove(int &, int &, std::string &, std::string &);
    bool playerAttack(int &, int &, int &, int &, std::string &);

    //Returns true if enemies can walk there, false otherwise.
    bool enemyWalkable(int Newx, int Newy);

    //Parse in any valid map
    void readMap();

    //update defender aggresiveness based on player location.
    void checkDefender(bool &defendermsg);


public:

    //Updates the map after each action
    void update();

    //Returns true if the level has ended, false otherwise
    bool endLevel();

    //Prompts the player to do something. Returns true if action successful.
    //actions are updated to returnmsg
    bool playerTurn(std::string , std::string , std::string &returnmsg);

    //All enemies do something. returns a string to describe actions of enemies
    std::string enemyTurn();

    //Starts level [currentLevel]
    void getLevel(int currentLevel);

    //Sets the player to the race specified
    void getPlayer(std::string type);

    //Returns end game message as a string
    std::string endgameCreds();

    //Checks whether player is dead
    bool playerDead();

    //prints the world to the output screen
    friend std::ostream &operator<<(std::ostream &out, World &w);

    explicit World(int totalLevels);
    ~World();
};

//coverts enemy char to type
std:: string eTypeConversion(char display);

#endif





