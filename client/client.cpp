#include "client.h"
#include "game_loop.h"
#include "client_game_state.h"


Client::Client(NetChannel& net_channel, ClientLobbySettings& lobby_settings)
    : channel(net_channel)
    , lobby_settings(lobby_settings)
    , display(command_queue, CLIENT_FPS)
    , receiver(state_queue, channel)
    , sender(command_queue, channel) {}

void Client::execute() {
    ClientGameState game_state(display);
    game_state.my_client_id = this->lobby_settings.id;
    display.camera.set_pos(0, 0);
    receiver.switch_game(game_state);
    sender.switch_game(game_state);

    receiver.start();
    sender.start();

    GameLoop game_loop(display, state_queue, lobby_settings.game_state_dto, game_state);
    game_loop.execute(display.event_handler, game_state);

    state_queue.close();
    command_queue.close();

    receiver.stop();
    sender.stop();

    channel.dissconect();

    receiver.join();
    sender.join();
}
