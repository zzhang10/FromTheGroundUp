#include "enemy.h"
#include <string>
#include <cmath>
#include <iostream>
#include "../subject.h"
#include "../globalSettings.h"

using namespace std;

Enemy::Enemy (int y, int x, char defaultChar, bool isHostile, int health,
        int defense, int attack): Subject(y, x, false, true, defaultChar),
        isHostile{isHostile}, hasSmartPointer{false}, health{health},
         defense{defense}, attack{attack}, maxhealth{health}{
    if (global__mode == 2) {
        // Multiplied stats in hard mode
        double Newh = health * global__multiplier;
        double Newa = attack * global__multiplier;
        double Newd = defense * global__multiplier;
        this->health = ceil(Newh);
        this->attack = ceil(Newa);
        this->defense = ceil(Newd);
        this->maxhealth = ceil(Newh);

    }
    // No attack strength in pleb mode
    if (global__mode == 0) this->attack = 0;
}

int Enemy::getAttacked(int dmgTaken){
    // Randomize damage taken from 0.8x to 1.2x
    float dmgMultiplier = 0.8 + ((float) rand()) / (float) RAND_MAX * (1.2 - 0.8);
    double trueDamage = ((100.0/ (100.0 + 2.0 * defense)) * dmgTaken) * dmgMultiplier;
    int roundDamage = ceil(trueDamage);
    this->setStats("h", health - roundDamage);
    return roundDamage;
}

int Enemy::getStats(string type) {
    if (type == "h") return health;
    else if (type == "d") return defense;
    else if (type == "a") return attack;
    else if (type == "isHostile") return isHostile;
    else if (type == "mh") return maxhealth;
    return 0;
}

void Enemy::setStats(string type, int amount){
    if (type == "h") health = amount;
    else if (type == "d") defense = amount;
    else if (type == "a") attack = amount;
    else if (type == "isHostile") isHostile = amount;
    if (health < 0) health = 0;
    if (defense < 0) defense = 0;
    if (amount < 0) attack = 0;
}

void Enemy :: protectingPos(int &x, int &y) {
    x = 0; y = 0;
}

void Enemy :: setProtPos(int x, int y) {

}

void Enemy::giveSmartPointer() {
    hasSmartPointer = true;
}

bool Enemy::gotSmartPointer() {
    return hasSmartPointer;
}

Enemy::~Enemy(){

}



