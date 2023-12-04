#ifndef _CLIENT_GAME_TURN_DISPLAYER_H_
#define _CLIENT_GAME_TURN_DISPLAYER_H_

#include <vector>
#include <unordered_map>
#include "game_display.h"

class GameTurnDisplayer {
    GameDisplay& display;
    int x,y;
    GameTextDisplay* header;
    std::vector<int> client_life;
    std::vector<GameTextDisplay*> turn_wheel;

    public:
    std::unordered_map<int, int> client_order;
    ~GameTurnDisplayer();
    GameTurnDisplayer(GameDisplay& display, const std::vector<int>& client_turn_order, int x, int y);
    void update(const std::vector<WormDto>& worms, const int active);
};
#endif