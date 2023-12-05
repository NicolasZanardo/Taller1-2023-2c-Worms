#include "client_receiver.h"
#include "client_game_state.h"
#include "client_game_state_dto.h"
#include <iostream>

ClientReceiver::ClientReceiver(
        Queue<std::shared_ptr<ClientGameStateDTO>>& state_queue, 
        NetChannel& net_channel
    ) : 
    state_queue(state_queue), 
    net_channel(&net_channel),
    state(nullptr)
    {}

void ClientReceiver::switch_game(ClientGameState& state) {
    this->state = &state;
}

void ClientReceiver::run() {
    while (Thread::keep_running_) {
        try {
            std::shared_ptr<NetMessage> msg(this->net_channel->read_message());
            msg->execute(*this);
        } catch (const ClosedQueue& e) {
            Thread::stop();
        }
    }
}

void ClientReceiver::run(NetMessageInitialGameState* msg) {
    auto game_state_dto = std::make_shared<ClientGameStateDTO>();

    game_state_dto->width = msg->room_width;
    game_state_dto->height = msg->room_height;
    game_state_dto->water_level_height = msg->water_height_level;
    game_state_dto->beams = std::move(msg->beams);
    game_state_dto->worms = std::move(msg->worms);
    game_state_dto->client_ids_turn_order = std::move(msg->client_ids_turn_order);
    
    this->state_queue.push(game_state_dto);
}

void ClientReceiver::run(NetMessageGameStateUpdate* msg) {
    auto game_state_dto = std::make_shared<ClientGameStateDTO>();

    game_state_dto->current_turn_client_id = msg->current_turn_client_id;
    game_state_dto->current_turn_worm_id = msg->current_turn_worm_id;
    game_state_dto->focused_entity_id = msg->focused_entity_id;
    game_state_dto->wind_speed = msg->wind_speed;
    game_state_dto->remaining_game_time = msg->remaining_game_time;
    game_state_dto->remaining_turn_time = msg->remaining_turn_time;
    
    game_state_dto->worms = std::move(msg->worms);
    game_state_dto->projectiles = std::move(msg->projectiles);
    game_state_dto->events = std::move(msg->events);
    game_state_dto->explosions = std::move(msg->explosions);

    this->state_queue.push(game_state_dto);
}

void ClientReceiver::run(NetMessageChat* msg) {
    // cout << "Client " << msg->client_id << " said: " << msg->chat << "\n";
}

void ClientReceiver::run(NetMessageLeave* msg) {
    // cli.stop();
    // cout << "Bye\n";
}

void ClientReceiver::run(NetMessageInformID* msg) {
    state->my_client_id = msg->client_id;
    std::cout << "I AM CLIENT "<< msg->client_id << "\n";
}

void ClientReceiver::run(NetMessage_test* msg) {
    // cout << "short: " << msg->test_short << " uint: " << msg->test_uint << " float: " << msg->test_float << " string: " << msg->test_string << "\n";
}


void ClientReceiver::run(NetMessageGameAction* msg) {
    // Client shouldnt receive
    // cout << "action for worm id: " << msg->client_id << "\n"; //<< " height: " << msg->room_height << " amount of beams on map: " << msg->beams.size() << "\n";
}

void ClientReceiver::run(NetMessagePlayerChangedWeapon* msg) {
    // Client shouldnt receive
    // cout << "action for worm id: " << msg->client_id << "\n"; //<< " height: " << msg->room_height << " amount of beams on map: " << msg->beams.size() << "\n";
}

void ClientReceiver::run(NetMessagePlayerChangedProjectileCountdown* msg) {
    // Client shouldnt receive
    // cout << "action for worm id: " << msg->client_id << "\n"; //<< " height: " << msg->room_height << " amount of beams on map: " << msg->beams.size() << "\n";
}

void ClientReceiver::run(NetMessageGameEnded* msg) {
    // TODO VICTORY/TIE/DEFEAT SCREEN flow
}