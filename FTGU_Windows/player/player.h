#ifndef PLAYER_H
#define PLAYER_H
#include "../subject.h"
#include <vector>

class Enemy;
class Cell;
class Item;

class Player : public Subject {
    //Player stats:
    int health;
    int defense;
    int attack;
    double gold;
    int maxHealth;
    int defaultDef;
    int defaultAtk;
    bool hasBarrier, hasSmartPointer;
    std::string race;

    //Performs calculation for player actions, and returns a message or
    //the amount as appropriate
    std::string uPotion(std::vector<std::tuple<std::string,std::string,int>>);
    int rAttack(int amount,bool truedmg);
    std::string pGold(std::string type, double amount);

    //Children classes must specify their stats (e.g, any special perks,
    // how much gold is worth, etc.
    virtual std::vector<std::tuple<std::string,std::string,int>> pStats() = 0;
    virtual double gStats(std::string type) = 0;

  public:
    //Restores to default atk and def at beginning of each level, also
    //sets hasSmartPointer to false.
    void restoreAtkDef();

    //Public methods for interacting with world(Abstract Template pattern)
    std::string usePotion();
    int receiveAttack(int amount, bool truedmg);
    std::string pickupGold(std::string type);

    //getters and setters, returns error message if appropriate.
    std::string getRace();
    bool gotSmartPointer();
    double getStat(std::string field);
    std::stringstream& setStat(std::stringstream &msg, std::string field,
                               double amount);

    Player(int x, int y, int h, int d, int a, std::string race);
    virtual ~Player() = 0;
};
#endif


