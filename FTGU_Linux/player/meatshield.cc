#include "meatshield.h"
#include "player.h"
#include <vector>
#include "../globalSettings.h"
using namespace std;

Meatshield:: Meatshield(int health, int attack, int defense, string race)
  : Player(0, 0, health, defense, attack, race) {}

vector<tuple<string,string,int>> Meatshield::pStats() {
   vector<tuple<string,string,int>>stats;
   if (global__modded) {
	stats.emplace_back("Restore Health II", "Health", 30);
        stats.emplace_back("Restore Health II", "Health", 30);
	stats.emplace_back("Restore Health", "Health", 10);
	stats.emplace_back("Regeneration", "Health", 10);
	stats.emplace_back("Regeneration", "Health", 10);
    }
    stats.emplace_back("Restore Health", "Health", 10);
    stats.emplace_back("Poison Health", "Health", -10);
    stats.emplace_back("Strength", "Attack", 5);
    stats.emplace_back("Wound Attack", "Attack", -5);
    stats.emplace_back("Resistance", "Defense", 5);
    stats.emplace_back("Wound Defense", "Defense", -5);
    return stats;
}


double Meatshield::gStats(string type) {
    if (type == "Normal") return 0.5;
    else if (type == "SmallStash") return 1.0;
    else if (type == "MercenaryStash") return 2.0;
    else if (type == "DefendedStash") return 3.0;
    return 0;
}


