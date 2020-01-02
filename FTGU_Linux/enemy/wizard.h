#ifndef WIZARD_H
#define WIZARD_H
#include "enemy.h"
#include "../globalSettings.h"
class Wizard final : public Enemy {
public:
    Wizard(int y, int x, char defaultChar = global__displayWizard,
            bool isHostile = true, int health = 60, int attack = 30,
            int defense = 12);
};
#endif


