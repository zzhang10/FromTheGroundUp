#ifndef ENEMY_H
#define ENEMY_H
#include "../subject.h"


class Enemy : public Subject{
    //Stats of the enemy
    bool isHostile, hasSmartPointer;
    int health, defense, attack, maxhealth;

 public:
    //Player calls this with its attack as parameter
    int getAttacked(int dmgTaken);

    //Sets x and y to reflect the coordinate of the item that the enemy is
    //protecting, if it is protecting something. Does nothing otherwise.
    virtual void protectingPos(int &x, int &y);

    //Getters and setters
    int getStats(std::string type);
    void setStats(std::string type, int amount);
    void giveSmartPointer();
    bool gotSmartPointer();
    virtual void setProtPos(int x, int y);

    Enemy(int y, int x, char defaultChar, bool isHostile, int health,
          int defense, int attack);

    //Abstract class
    ~Enemy() = 0;
};

#endif


