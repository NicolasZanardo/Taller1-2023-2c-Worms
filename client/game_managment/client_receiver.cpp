#include "client_receiver.h"

#include "client_game_state_dto.h"

// ClientReceiver::ClientReceiver(Queue<GameEvent>& state_queue, Queue<GameEvent>& echo_queue)
//     : state_queue(state_queue), echo_queue(echo_queue) {}

// explicit ClientReceiver(Queue<GameEvent>& state_queue, NetChannel& net_channel)
//     : state_queue(state_queue), net_channel(&net_channel) {}

ClientReceiver::ClientReceiver(Queue<std::shared_ptr<ClientGameStateDTO>>& state_queue, NetChannel& net_channel)
    : state_queue(state_queue), net_channel(&net_channel) {}

void ClientReceiver::run() {
    while (Thread::keep_running_) {
        try {
            // GameEvent game_event = this->echo_queue.pop();
            std::cout << "Receiver waiting for a message\n";
            std::shared_ptr<NetMessage> msg(this->net_channel->read_message());

            msg->execute(*this);

            // this->state_queue.push(game_event);
        } catch (const ClosedQueue& e) {
            Thread::stop();
        }
    }
}

void ClientReceiver::run(NetMessageInitialGameState* msg) {
    std::cout << "Receiving initial game state.\n";
    auto game_state_dto = std::make_shared<ClientGameStateDTO>();

    game_state_dto->width = msg->room_width;
    game_state_dto->height = msg->room_height;

    std::cout << "w: " << msg->room_width << " - h: " << msg->room_height << '\n';
    std::cout << "worms in msg " << msg->worms.size() << '\n';

    game_state_dto->beams = std::move(msg->beams);
    game_state_dto->worms = std::move(msg->worms);

    this->state_queue.push(game_state_dto);
}

void ClientReceiver::run(NetMessageGameStateUpdate* msg) {
    std::cout << "Receiving update game state\n";
    auto game_state_dto = std::make_shared<ClientGameStateDTO>();

    game_state_dto->active_client_id = msg->active_client_id;
    game_state_dto->active_entity_id = msg->active_entity_id;
    game_state_dto->wind_speed = msg->wind_speed;
    game_state_dto->remaining_game_time = msg->remaining_game_time;
    game_state_dto->remaining_turn_time = msg->remaining_turn_time;
    
    game_state_dto->worms = std::move(msg->worms);
    game_state_dto->bullets = std::move(msg->bullets);
    game_state_dto->events = std::move(msg->events);

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
    // cout << "I AM CLIENT "<< msg->client_id << "\n";
}

void ClientReceiver::run(NetMessage_test* msg) {
    // cout << "short: " << msg->test_short << " uint: " << msg->test_uint << " float: " << msg->test_float << " string: " << msg->test_string << "\n";
}


void ClientReceiver::run(NetMessageGameAction* msg) {
    // Client shouldnt receive
    // cout << "action for worm id: " << msg->client_id << "\n"; //<< " height: " << msg->room_height << " amount of beams on map: " << msg->beams.size() << "\n";
}
