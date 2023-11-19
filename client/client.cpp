#include "client.h"

#include <cmath>
#include <chrono>
#include <thread>

#include "game_loop.h"
#include "client_game_state.h"

Client::Client(const char* host_name, const char* service_name)
    : channel(host_name, service_name), display(event_queue, 25)
    , receiver(state_queue, channel)
    , sender(event_queue, channel)
     {}

void Client::execute() {
    ClientGameState game_state(display);

    receiver.start();
    sender.start();

    GameLoop game_loop(display, state_queue);
    game_loop.execute(display.event_handler, game_state);

    event_queue.close();
    echo_queue.close();
    state_queue.close();

    receiver.join();
    sender.join();
}
