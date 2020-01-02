#ifndef HACKER_H
#define HACKER_H
#include "player.h"

class Hacker final : public Player {
    std::vector<std::tuple<std::string,std::string,int>> pStats() override ;
    double gStats(std::string type) override;
public:
    explicit Hacker(int health = 15000, int attack = 500, int defense = 500,
                   std::string race = "Hacker");
};
#endif


