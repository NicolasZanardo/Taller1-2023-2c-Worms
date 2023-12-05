#include "client.h"

#include <cmath>
#include <chrono>
#include <thread>

#include "game_loop.h"
#include "client_game_state.h"

// Client::Client(const char *host_name, const char *service_name)
//     : channel(host_name, service_name),
//       display(command_queue, CLIENT_FPS), receiver(state_queue, channel), sender(command_queue, channel) {}

Client::Client(NetChannel& net_channel, ClientLobbySettings& lobby_settings)
    : channel(net_channel)
    , lobby_settings(lobby_settings)
    , display(command_queue, CLIENT_FPS)
    , receiver(state_queue, channel)
    , sender(command_queue, channel) {}

void Client::execute() {
    std::cout << "Ejecutando SDL\n";
    ClientGameState game_state(display);
    std::cout << "Ejecutando SDL2\n";
    game_state.my_client_id = this->lobby_settings.id;
    std::cout << "Ejecutando SDL3\n";
    display.camera.set_pos(0, 0);
    std::cout << "Ejecutando SDL4\n";
    receiver.switch_game(game_state);
    std::cout << "Ejecutando SDL5\n";
    sender.switch_game(game_state);
    std::cout << "Ejecutando SDL6\n";


    receiver.start();
    sender.start();

    GameLoop game_loop(display, state_queue);
    game_loop.execute(display.event_handler, game_state);

    command_queue.close();
    state_queue.close();

    receiver.join();
    sender.join();
}
