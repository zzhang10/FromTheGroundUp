#include "middleman.h"
#include "player.h"
#include <vector>
#include "../globalSettings.h"

using namespace std;

Middleman :: Middleman(int health, int attack, int defense, string race)
        : Player(0, 0, health, defense, attack, race) {}

vector<tuple<string,string,int>> Middleman::pStats() {
    vector<tuple<string,string,int>>stats;
    if (global__modded) {
	stats.emplace_back("Compound", "every stat", 10);
	stats.emplace_back("Compound", "every stat", 10);
	stats.emplace_back("Compound", "every stat", 10);
    }
    stats.emplace_back("Restore Health", "Health", 10);
    stats.emplace_back("Poison Health", "Health", -10);
    stats.emplace_back("Strength", "Attack", 5);
    stats.emplace_back("Wound Attack", "Attack", -5);
    stats.emplace_back("Resistance", "Defense", 5);
    stats.emplace_back("Wound Defense", "Defense", -5);
    return stats;
}



double Middleman::gStats(string type) {
    if (type == "Normal") return 1.0;
    else if (type == "SmallStash") return 2.0;
    else if (type == "MercenaryStash") return 4.0;
    else if (type == "DefendedStash") return 6.0;
    return 0;
}




