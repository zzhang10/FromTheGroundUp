#include "wizard.h"
#include "enemy.h"
using namespace std;

Wizard::Wizard(int y, int x, char defaultChar, bool isHostile, int health,
    int attack, int defense) : Enemy(y, x, defaultChar,isHostile,health,
    defense, attack){}

