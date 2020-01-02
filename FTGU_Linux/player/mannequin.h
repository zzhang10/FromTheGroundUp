#ifndef MANNEQUIN_H
#define MANNEQUIN_H
#include "player.h"

class Mannequin final : public Player {
    std::vector<std::tuple<std::string,std::string,int>> pStats() override ;
    double gStats(std::string type) override;
  public:
    explicit Mannequin(int health = 160, int attack = 30, int defense = 30,
            std::string race = "Mannequin");
};
#endif


