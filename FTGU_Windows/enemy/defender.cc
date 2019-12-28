#include "defender.h"
#include "enemy.h"
#include "../globalSettings.h"
using namespace std;

Defender::Defender (int y, int x, int defx, int defy, char defaultChar, bool
    isHostile, int health, int attack, int defense): Enemy(y, x,defaultChar,
    isHostile, health, defense, attack), defx{defx}, defy{defy} {
    if (global__hacker) isHostile = true;
}


void Defender:: protectingPos(int &x, int &y) {
    x = defx;
    y = defy;
}

void Defender::setProtPos(int x, int y){
    defx = x;
    defy = y;
}


