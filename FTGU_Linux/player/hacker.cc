#include "hacker.h"
#include "player.h"
#include <vector>

using namespace std;

Hacker :: Hacker(int health, int attack, int defense, string race)
        : Player(0, 0, health, defense, attack, race) {}

vector<tuple<string,string,int>> Hacker::pStats() {
    vector<tuple<string,string,int>>stats;
    stats.emplace_back("Regeneration", "Health", 10);
    stats.emplace_back("Wound Health", "Health", -10);
    stats.emplace_back("Strength", "Attack", 5);
    stats.emplace_back("Wound Attack", "Attack", -5);
    stats.emplace_back("Resistance", "Defense", 5);
    stats.emplace_back("Wound Defense", "Defense", -5);
    return stats;
}



double Hacker::gStats(string type) {
    if (type == "Normal") return 100.0;
    else if (type == "SmallStash") return 200.0;
    else if (type == "MercenaryStash") return 400.0;
    else if (type == "DefendedStash") return 600.0;
    return 0;
}




