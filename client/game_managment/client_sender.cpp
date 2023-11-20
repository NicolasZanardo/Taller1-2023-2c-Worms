#include "client_sender.h"
#include "client_game_state.h"
#include <iostream>

ClientSender::ClientSender(Queue<GameEvent>& event_queue, NetChannel& net_channel)
    : event_queue(event_queue)
    , net_channel(&net_channel) 
    , state(nullptr)
    {}

void ClientSender::switch_game(ClientGameState& state) {
    this->state = &state;
}

void ClientSender::run() {
    while (Thread::keep_running_) {
        try {
            GameEvent game_event = this->event_queue.pop();
            if (state->my_client_id < 1)
                continue;

            auto net_message = game_event_to_net_message(game_event);
            net_channel->send_message(*net_message);
        } catch (const ClosedQueue& e) {
            Thread::stop();
        }
    }
}

// TODO Do elsewhere
std::shared_ptr<NetMessage> ClientSender::game_event_to_net_message(GameEvent event) {
    switch (event) {
        case GameEvent::MOVE_LEFT_INIT:
            return std::make_shared<NetMessageGameAction>(
                state->my_client_id, ActionTypeDto::moving_left_init
            );
        case GameEvent::MOVE_LEFT_END:
            return std::make_shared<NetMessageGameAction>(
                state->my_client_id, ActionTypeDto::stop_moving
            );
        case GameEvent::MOVE_RIGHT_INIT:
            return std::make_shared<NetMessageGameAction>(
                state->my_client_id, ActionTypeDto::moving_right_init
            );
        case GameEvent::MOVE_RIGHT_END:
            return std::make_shared<NetMessageGameAction>(
                state->my_client_id, ActionTypeDto::stop_moving
            );
        case GameEvent::JUMP_FORWARD:
            return std::make_shared<NetMessageGameAction>(
                state->my_client_id, ActionTypeDto::jump_forward
            );
        case GameEvent::JUMP_BACKWARDS:
            return std::make_shared<NetMessageGameAction>(
                state->my_client_id, ActionTypeDto::jump_back
            );
    }
    return std::make_shared<NetMessageGameAction>(
        state->my_client_id, ActionTypeDto::stop_moving
    );
}

