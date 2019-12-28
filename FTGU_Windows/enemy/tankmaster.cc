#include "tankmaster.h"
#include "enemy.h"
using namespace std;

Tankmaster::Tankmaster(int y, int x, char defaultChar, bool isHostile, int health,
    int attack, int defense) : Enemy(y, x, defaultChar,isHostile,
    health, defense, attack){}


