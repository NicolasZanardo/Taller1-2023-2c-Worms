#include "client_reciever.h"

#include "client.h"

Reciever::Reciever(const int client_id, Client& client, NetChannel* channel, NetQueue& send_queue, GamesManager& games_manager) : 
    Thread(), 
    client_id(client_id),
    client(&client),
    channel(channel),
    send_queue(&send_queue),
    games_manager(&games_manager)
    {}

Reciever::~Reciever() {
    join();
}

void Reciever::run() {
    while (keep_running_) {
        try {
            std::shared_ptr<NetMessage> msg(channel->read_message());
            msg->execute(*this);
            // if (game_queue != nullptr)
            //     game_queue->push(msg);
        } catch (const std::exception& ex) {
            keep_running_ = false;
        }
    }
}

void Reciever::stop() {
    keep_running_ = false;
    game_queue = nullptr;
}

void Reciever::switch_lobby(NetQueue* new_game_queue) {
    game_queue = new_game_queue;
}

void Reciever::run(NetMessageCreateGame* msg) {
    bool success = this->games_manager->createGame(msg->game_room, msg->scenario, msg->num_players);

    std::shared_ptr<NetMessage> response = std::make_shared<NetMessageCreateGameResponse>(success);

    this->send_queue->push(response);
}

void Reciever::run(NetMessageListGames* msg) {
    std::list<GameInfoDTO> info_list = this->games_manager->listGames();

    std::shared_ptr<NetMessage> response = std::make_shared<NetMessageListGamesResponse>(std::move(info_list));

    this->send_queue->push(response);
}

void Reciever::run(NetMessageJoinGame* msg) {
    bool success = this->games_manager->joinGame(msg->game_room, *(this->client));

    std::shared_ptr<NetMessage> response = std::make_shared<NetMessageJoinGameResponse>(success);

    this->send_queue->push(response);

    // set game queue.
}

void run(NetMessageStartGame* msg) {
    // game.start();
}

