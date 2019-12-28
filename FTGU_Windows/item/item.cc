#include "item.h"
#include <string>
#include <iostream>
#include "../globalSettings.h"
using namespace std;


//ITEM CLASS------------------------------------------------------------------
Item::Item(int y, int x, string itemType, bool canStepon, char c)
  : Subject(y, x, canStepon, false, c), itemType{itemType} {}

tuple<string, double, bool> Item::getInfo() {
	return make_tuple(itemType, 0.0, false);
}

void Item::setProtect(bool isProtected){
    cerr<< "this item currently does not support defender protection." << endl;
}

Item::~Item(){}

void Item::getDefPos(int &px, int &py) {
    cerr<<"Currently not protected.";
}
void Item::setDefPos(int px, int py) {
    cerr<<"Currently not protected.";
}



//GOLD CLASS------------------------------------------------------------------

Gold :: Gold(int y, int x, string goldType, pair<int, int> defenderat)
  : Item(y, x, goldType, true, global__displayGold), defenderProtect{false},
  defenderat{defenderat}{
    if (goldType == "DefendedStash") {
        defenderProtect = true;
        setSteppable(false);
    }
}

tuple<string, double, bool> Gold::getInfo() {
    double n = 0.0;
    if (itemType == "DefendedStash") n = 6.0;
    else if (itemType == "MercenaryStash") n = 4.0;
    else if (itemType == "SmallStash") n = 2.0;
    else if (itemType == "Normal") n = 1.0;
    return make_tuple(itemType, n, defenderProtect);
}

void Gold:: setProtect(bool isProtected){
    defenderProtect = isProtected;
}

void Gold::getDefPos(int &px, int &py) {
    px = defenderat.first;
    py = defenderat.second;
}
void Gold::setDefPos(int px, int py) {
    defenderat = make_pair(px, py);
}


//ForceShield Class ------------------------------------------------------------

ForceShield::ForceShield(int y, int x, std::pair<int, int> defenderat)
        : Item(y, x, "Fshld", false, global__displayForceShield), defenderProtect{true},
        defenderat{defenderat} {}

void ForceShield:: setProtect(bool isProtected){
    defenderProtect = isProtected;
}

tuple<string, double, bool> ForceShield::getInfo() {
    return make_tuple(itemType, 0, defenderProtect);
}

void ForceShield::getDefPos(int &px, int &py) {
    px = defenderat.first;
    py = defenderat.second;
}
void ForceShield::setDefPos(int px, int py) {
    defenderat = make_pair(px, py);
}


//SmartPointer Class------------------------------------------------------------
SmartPointer::SmartPointer(int y, int x): Item(y, x, "SmartPointer", true,
        global__displaySmartPtr) {}


//Potion Class------------------------------------------------------------------
Potion::Potion(int y, int x, string type): Item(y, x, "Potion", false,
        global__displayPotion), type{type} {}
tuple<string, double, bool> Potion::getInfo() {
    return make_tuple(type, 1, 1);
}



