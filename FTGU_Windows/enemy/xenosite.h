#ifndef XENOSITE_H
#define XENOSITE_H
#include "enemy.h"
#include "../globalSettings.h"
class Xenosite final : public Enemy {
public:
    Xenosite(int y, int x, char defaultChar =global__displayXenosite ,
            bool isHostile = true, int health = 60 , int attack = 0 ,
            int defense = 25);
};
#endif



