#ifndef VINDICATOR_H
#define VINDICATOR_H
#include "enemy.h"
#include "../globalSettings.h"
class Vindicator final : public Enemy {
public:
    Vindicator(int y, int x, char defaultChar = global__displayVindicator,
            bool isHostile = true, int health = 80 , int attack = 15 ,
            int defense = 15);
};
#endif


