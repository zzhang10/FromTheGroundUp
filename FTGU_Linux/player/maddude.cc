#include "maddude.h"
#include "player.h"
#include <vector>
#include "../globalSettings.h"
using namespace std;

Maddude:: Maddude(int health, int attack, int defense, string race)
        : Player(0, 0, health, defense, attack, race) {}

vector<tuple<string,string,int>> Maddude::pStats() {
    vector<tuple<string,string,int>>stats;
    if (global__modded) {
        stats.emplace_back("Strength II", "Attack", 10);
	stats.emplace_back("Strength II", "Attack", 10);
	stats.emplace_back("Strength", "Attack", 5);
	stats.emplace_back("Strength", "Attack", 5);
	stats.emplace_back("Strength", "Attack", 5);
    }
    stats.emplace_back("Restore Health", "Health", 10);
    stats.emplace_back("Poison Health(But with MADDUDE PERKS!)", "Health", 10);
    stats.emplace_back("Strength", "Attack", 5);
    stats.emplace_back("Wound Attack(But with MADDUDE PERKS!)", "Attack", 5);
    stats.emplace_back("Resistance", "Defense", 5);
    stats.emplace_back("Wound Defense(But with MADDUDE PERKS!)", "Defense", 5);
    return stats;
}


double Maddude::gStats(string type) {
    if (type == "Normal") return 1.0;
    else if (type == "SmallStash") return 2.0;
    else if (type == "MercenaryStash") return 4.0;
    else if (type == "DefendedStash") return 6.0;
    return 0;
}



