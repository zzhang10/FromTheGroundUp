#ifndef MERCENARY_H
#define MERCENARY_H
#include "enemy.h"
#include "../globalSettings.h"
class Mercenary final : public Enemy {
public:
    Mercenary(int y, int x, char defaultChar = global__displayMercenary ,
            bool isHostile = false,int health = 30 , int attack = 60 ,
            int defense = 1 );
};
#endif



