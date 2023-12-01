#include "game_timer.h"
#include <iomanip>
#include <sstream>

const int MS = 1000;

GameTimer::GameTimer(GameDisplay &display) :
    last_updated_game_time(0),
    last_updated_turn_time(0),
    game_time_display(
        display.new_text(
std::to_string(last_updated_game_time),
        748, 12,
        TextAlign::left,
        TextLayer::UI,
        TextType::gametext
    )),
    turn_time_display(
        display.new_text(
            std::to_string(last_updated_turn_time),
            390, 42,
            TextAlign::left,
            TextLayer::UI,
            TextType::gametext
        )) {}

void GameTimer::update(int updated_turn_time, int updated_game_time) {

    if (updated_game_time / MS != last_updated_game_time / MS) {
        game_time_display->update(to_minutes_seconds_format(updated_game_time / MS));
        last_updated_game_time = updated_game_time;
    }

    if (updated_turn_time / MS != last_updated_turn_time / MS) {
        if (updated_turn_time / MS == 0) {
            turn_time_display->hidden(true);
        } else {
            turn_time_display->hidden(false);
        }
        turn_time_display->update(std::to_string(updated_turn_time / MS));
        last_updated_turn_time = updated_turn_time;
    }
}

std::string GameTimer::to_minutes_seconds_format(int seconds) {
    int minutes = seconds / 60;
    int remainingSeconds = seconds % 60;

    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << minutes << " : "
        << std::setw(2) << std::setfill('0') << remainingSeconds;

    return oss.str();
}
