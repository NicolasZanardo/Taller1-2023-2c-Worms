#ifndef TP_WORMS_CHEATMANAGER_H
#define TP_WORMS_CHEATMANAGER_H

#include <unordered_map>
#include "CheatType.h"

class Worm;

class CheatManager {
    std::unordered_map<CheatType, bool> cheat_map;
    const int refill_ammo = 10;
    const float cheat_damage = 300;
public:
    CheatManager();
    void toggle_cheat(CheatType cheat, std::shared_ptr<Worm> worm);
};


#endif //TP_WORMS_CHEATMANAGER_H
