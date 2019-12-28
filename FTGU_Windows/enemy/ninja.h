#ifndef NINJA_H
#define NINJA_H
#include "enemy.h"
#include "../globalSettings.h"
class Ninja final : public Enemy {
public:
    Ninja(int y, int x, char defaultChar = global__displayNinja,
    bool isHostile = true, int health = 70, int attack = 5,int defense = 10);
};
#endif


