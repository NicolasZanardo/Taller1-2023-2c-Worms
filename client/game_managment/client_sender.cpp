#include "client_sender.h"
#include "client_game_state.h"
#include <iostream>

ClientSender::ClientSender(Queue<std::shared_ptr<Command>> &command_queue, NetChannel& net_channel)
    : command_queue(command_queue)
    , net_channel(&net_channel) 
    , state(nullptr)
    {}

void ClientSender::switch_game(ClientGameState& new_state) {
    this->state = &new_state;
}

void ClientSender::run() {
    while (Thread::keep_running_) {
        try {
            std::shared_ptr<Command> command = this->command_queue.pop();
            if (state->my_client_id < 1)
                continue;
            auto net_message = command->create_net_message(state->my_client_id);
            net_channel->send_message(*net_message);
        } catch (const ClosedQueue& e) {
            Thread::stop();
        }
    }
}

