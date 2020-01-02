#ifndef MADDUDE_H
#define MADDUDE_H
#include "player.h"


class Maddude final : public Player{
    std::vector<std::tuple<std::string,std::string,int>> pStats() override ;
    double gStats(std::string type) override;
  public:
    explicit Maddude(int health = 240, int attack = 40, int defense = 20,
            std::string race = "Maddude");
};

#endif



