#ifndef DEFENDER_H
#define DEFENDER_H
#include "enemy.h"
#include "../globalSettings.h"
class Defender final : public Enemy{
    int defx, defy;
public:
    Defender(int y, int x, int defx, int defy,
            char defaultChar = global__displayDefender, bool isHostile = false,
            int health = 200, int attack = 5, int defense = 30);
    void protectingPos(int &x, int &y) override;
    void setProtPos(int x, int y)override;
};
#endif


