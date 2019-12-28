#ifndef TANKMASTER_H
#define TANKMASTER_H
#include "enemy.h"
#include "../globalSettings.h"
class Tankmaster final : public Enemy {
public:
    Tankmaster(int y, int x, char defaultChar = global__displayTankmaster,
            bool isHostile = true, int health =110 , int attack = 20,
            int defense =25 );
};
#endif



