#ifndef MEATSHIELD_H
#define MEATSHIELD_H
#include "player.h"

class Meatshield final : public Player {
    std::vector<std::tuple<std::string,std::string,int>> pStats() override ;
    double gStats(std::string type) override;
  public:
    explicit Meatshield(int health = 350, int attack = 40, int defense = 35,
            std::string race = "Meatshield");
};
#endif



