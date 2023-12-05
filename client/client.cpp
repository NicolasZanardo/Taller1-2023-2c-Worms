#include "client.h"
#include <iostream>
#include "game_loop.h"
#include "client_game_state.h"

Client::Client(const char *host_name, const char *service_name) 
    : command_queue()
    , state_queue()
    , channel(host_name, service_name)
    , display(command_queue, CLIENT_FPS)
    , receiver(state_queue, channel)
    , sender(command_queue, channel)
    {}

void Client::execute() {
    ClientGameState game_state(display);
    //display.camera.set_pos(0, 0);
    receiver.switch_game(game_state);
    sender.switch_game(game_state);


    receiver.start();
    sender.start();

    GameLoop game_loop(display, state_queue);
    game_loop.execute(display.event_handler, game_state);
    std::cout << "1-TERMINE DE CORRER!!\n";

    state_queue.close();
    command_queue.close();
    std::cout << "2-COLAS CERRADAS!!\n";

    receiver.stop();
    sender.stop();
    std::cout << "3-HILOS DETENIDOS!!\n";
    
    channel.dissconect();
    std::cout << "4-CONECCION CORTADA!!\n";

    receiver.join();
    sender.join();
    std::cout << "5-HILOS JUNTADOS!!\n";
}
