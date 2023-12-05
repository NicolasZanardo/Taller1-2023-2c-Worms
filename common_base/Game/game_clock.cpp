#include "game_clock.h"
#include <thread>
using namespace std::chrono;


GameClock::GameClock(int fps) :
    fps(fps), frame_rate(1000000 / fps),
    iteration(1000000.0f/(double)fps),
    prev_iteration(0), start(steady_clock::now())
    { }

void GameClock::sync() {
    prev_iteration = iteration;
    time_point t2 = steady_clock::now();
    microseconds rest = frame_rate - duration_cast<microseconds>(t2 - start);
    if (rest.count() < 0) {
        microseconds behind = -rest;
        microseconds lost = behind - (behind % frame_rate);
        start += lost;
        iteration += lost.count() / frame_rate.count();
    } else {
        std::this_thread::sleep_for(rest);
    }

    start += frame_rate;
    iteration += 1000000.0f/(double)fps;
}

double GameClock::delta() {
    return iteration - prev_iteration;
}
