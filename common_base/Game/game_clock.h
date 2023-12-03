#ifndef GAME_CLOCK_H
#define GAME_CLOCK_H

#include <chrono>

class GameClock {
    int fps;
	std::chrono::microseconds frame_rate;
    double iteration;
    double prev_iteration;
    std::chrono::time_point<std::chrono::steady_clock, std::chrono::steady_clock::duration> start;
    

    public:
    GameClock(int fps);
    void sync();
    double delta();
};

#endif