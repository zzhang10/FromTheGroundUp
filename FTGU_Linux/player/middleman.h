#ifndef MIDDLEMAN_H
#define MIDDLEMAN_H
#include "player.h"

class Middleman final : public Player {
    std::vector<std::tuple<std::string,std::string,int>> pStats() override ;
    double gStats(std::string type) override;
  public:
    explicit Middleman(int health = 240, int attack = 30, int defense = 30,
            std::string race = "Middleman");
};
#endif


