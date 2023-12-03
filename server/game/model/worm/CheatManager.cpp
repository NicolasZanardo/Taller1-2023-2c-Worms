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
        case CheatType::HEALTH: {
            if (toggled_on) {
                // worm->body = std::make_shared<WormCheatBody>(std::move(worm->body));
            } else {
                // worm->body = std::make_shared<WormBody>(std::move(worm->body));
            }
        }
            break;
        case CheatType::MOVEMENT: {
            worm->cheat_movement(toggled_on);
        }
            break;
        case CheatType::WEAPON: {
        }
            break;
    }
}
