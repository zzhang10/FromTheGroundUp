#include "mercenary.h"
#include "enemy.h"
using namespace std;

Mercenary::Mercenary(int y, int x, char defaultChar, bool isHostile, int health,
    int attack, int defense) : Enemy(y, x, defaultChar,isHostile,health,
    defense, attack) {}


