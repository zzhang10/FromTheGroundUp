#include "player.h"
#include <iostream>
#include <sstream>
#include "../display/cell.h"
#include "../item/item.h"
#include "../globalSettings.h"

using namespace std;

Player::Player(int x, int y, int h, int d, int a, string race)
  : Subject(y, x, false, true, global__displayPlayer), health{h}, 
  defense{d}, attack{a}, gold{0}, maxHealth{h}, defaultDef{d}, 
  defaultAtk{a}, hasBarrier{false}, hasSmartPointer{false}, race{race}{
    if (global__modded) {
	if (this->race == "Meatshield") {
	    this->maxHealth = 800;
            this->health = 800;
            this->attack = 35;
            this->defaultAtk = 35;
	    this->defense = 5;
	    this->defaultDef = 5;
	} else if (this->race == "Middleman") {
	    this->maxHealth = 480;
            this->health = 480;
            this->attack = 30;
            this->defaultAtk = 30;
	    this->defense = 40;
	    this->defaultDef = 40;
	} else if (this->race == "Maddude") {
	    this->maxHealth = 350;
            this->health = 350;
            this->attack = 80;
            this->defaultAtk = 80;
	    this->defense = 20;
	    this->defaultDef = 20;
	} else if (this->race == "Mannequin") {
	    this->maxHealth = 600;
            this->health = 600;
            this->attack = 20;
            this->defaultAtk = 20;
	    this->defense = 125;
	    this->defaultDef = 125;
	}
  }
}

string Player::uPotion(vector<tuple<string, string, int>> stats){
    stringstream s1{""};
    int choiceNumber = stats.size();
    int choice = rand() % choiceNumber;
    string potionName = get<0>(stats[choice]);
    string effectType = get<1>(stats[choice]);
    int amt = get<2>(stats[choice]);
    s1 << "You used a " << potionName << " potion which ";
    if (amt >= 0) s1 << "increases";
    else if (amt < 0) s1 << "decreases";
    s1 <<" your " << effectType << " by ";
    if (amt >= 0) s1 << amt << "." << endl;
    else if (amt < 0) s1 << -amt << "." << endl;
    if (effectType == "Health") {
        this->setStat(s1, "h", this->getStat("h") + amt);
    }
    else if (effectType == "Attack") {
        this->setStat(s1, "a", this->getStat("a") + amt);
    }
    else if (effectType == "Defense") {
        this->setStat(s1, "d", this->getStat("d") + amt);
    }
    else if (effectType == "every stat") {
        this->setStat(s1, "d", this->getStat("d") + amt);
	    this->setStat(s1, "a", this->getStat("a") + amt);
	    this->setStat(s1, "h", this->getStat("h") + amt);
    }

    return s1.str();

}


string Player::pGold(string type, double amount) {
    stringstream s1{""};
    string name;
    if (type == "Normal") name = "normal pile of gold";
    else if (type == "SmallStash") name = "small stash of gold";
    else if (type == "MercenaryStash") name = "Mercenary Stash";
    else if (type == "DefendedStash") name = "Defender Stash";
    s1 <<" and picked up a " << name << " which is worth ";
    s1 << amount << "." << endl;
    this->setStat(s1, "g", this->getStat("g") + amount);
    return s1.str();
}

bool Player:: gotSmartPointer() {
    return hasSmartPointer;
}

int Player::rAttack(int amount, bool truedmg){
    if (global__mode == 0) return 0;
    // Randomize damage received from 0.8x to 1.2x
    float dmgMultiplier = 0.8 + ((float) rand()) / (float) RAND_MAX * (1.2 - 0.8);
    double receivedDmg = (100.0/(100.0 + 2.0 * defense)) * amount *dmgMultiplier;
    int roundedDmg = receivedDmg;
    if (hasBarrier) {
        roundedDmg += 1;
        roundedDmg /= 2;
    }
    if (truedmg) roundedDmg = amount;
    this->health -= roundedDmg;
    if (health < 0) health = 0;
    return roundedDmg;
}

int Player::receiveAttack(int amount, bool truedmg) {
    int x = 0;
    if (truedmg) x = rand() % 3; //wizards do true damage with 67% miss, 33 % hit
    else x = rand() % 4;// Otherwise regular damage with 50% miss, 50% hit
    if (x == 0 || x == 1) return -1;
    else return rAttack(amount, truedmg);
}

string Player::usePotion() {
    return uPotion(pStats());
}

string Player::pickupGold(string type) {
    if ((type != "FS") && (type != "C") && (type != "DROP")) {
        return pGold(type, gStats(type));
    }
    else if (type == "C"){
        this->hasSmartPointer = true;
        stringstream s1{""};
        s1 << " and snagged the SmartPointer!" << endl;
        return s1.str();
    } else if (type == "DROP") {
        this->gold += 1.0;
        return "";
    } else {
        this->hasBarrier = true;
        stringstream s1{""};
        s1 << endl;
        return s1.str();
    }
}

double Player::getStat(string field){
    if (field == "a") return attack;
    else if (field == "d") return defense;
    else if (field == "h") return health;
    else if (field == "g") return gold;
    else if (field == "mh") return maxHealth;
    else return 0;
}

string Player::getRace() {
    return race;
}

std::stringstream& Player::setStat(stringstream &msg, string field,
        double amount){
    if (field == "a"){
        if (amount >= 0) attack = amount;
        else {
            msg << "But your attack cannot be negative." << endl;
            attack = 0;
        }
    }
    else if (field == "d"){
        if (amount >= 0) defense = amount;
        else {
            msg << "But your defense cannot be negative." << endl;
            defense = 0;
        }
    }
    else if (field == "h") {
        if (amount > maxHealth) {
            msg << "But your Max health is " << maxHealth << endl;
            health = maxHealth;
        } else if (amount < 0) {
	    health = 0;
    	} else {
            health = amount;
        }
    } else if (field == "g") {
        this->gold = amount;
        if (this->gold < 0) {
            this->gold = 0;
            msg << "But you cannot have negative gold." << endl;
        }
    }
    return msg;
}

void Player::restoreAtkDef(){
    attack = defaultAtk;
    defense = defaultDef;
    hasSmartPointer = false;
}

Player :: ~Player() {

}




