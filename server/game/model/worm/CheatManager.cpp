#include "CheatManager.h"
#include "Worm.h"
#include "WormCheatBody.h"
#include "WormBody.h"

CheatManager::CheatManager() : cheat_map{
    {CheatType::MOVEMENT, false},
    {CheatType::HEALTH,   false},
    {CheatType::WEAPON,   false}
} {}

void CheatManager::toggle_cheat(CheatType cheat, std::shared_ptr<Worm> worm) {
    cheat_map[cheat] = !cheat_map.at(cheat);
    auto toggled_on = cheat_map.at(cheat);
    switch (cheat) {
        case CheatType::HEALTH:
            worm->cheat_health();
            break;
        case CheatType::MOVEMENT:
            worm->cheat_movement(toggled_on);
            break;
        case CheatType::WEAPON:
            worm->cheat_weapon(refill_ammo, cheat_damage);
            break;
    }
}
