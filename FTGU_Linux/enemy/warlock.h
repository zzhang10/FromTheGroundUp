#ifndef WARLOCK_H
#define WARLOCK_H

#include "enemy.h"
#include "../globalSettings.h"
class Warlock final : public Enemy {

public:
    Warlock(int y, int x, char defaultChar = global__displayWarlock,
            bool isHostile = true,int health = 140, int attack = 20,
            int defense = 10 );

};
#endif

