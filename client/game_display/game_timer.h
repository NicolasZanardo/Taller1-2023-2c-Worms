#ifndef TP_WORMS_GAME_TIMER_H
#define TP_WORMS_GAME_TIMER_H

#include "game_text_display.h"
#include "game_display.h"

class GameTimer {
    int last_updated_game_time = 0;
    int last_updated_turn_time = 0;
    GameTextDisplay* game_time_display;
    GameTextDisplay* turn_time_display;

    static std::string to_minutes_seconds_format(int seconds);

public:
    explicit GameTimer(GameDisplay& display);
    void update(int turn_time, int game_time);
};

#endif //TP_WORMS_GAME_TIMER_H
