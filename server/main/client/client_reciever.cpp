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
            // std::shared_ptr<NetMessage> msg(channel->read_message());
            this->msg = std::shared_ptr<NetMessage>(channel->read_message());
            this->msg->execute(*this);
            // msg->execute(*this);
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
    std::cout << "room: " << msg->game_room << "- scenario: " << msg->scenario << " - players: " <<  msg->num_players << "was created\n";
    bool success = this->games_manager->createGame(msg->game_room, msg->scenario, msg->num_players);

    std::shared_ptr<NetMessage> response = std::make_shared<NetMessageCreateGameResponse>(success);

    this->send_queue->push(response);
}

void Reciever::run(NetMessageListGames* msg) {
    std::cout << "Listed games for client: " << this->client_id << "\n";
    std::list<GameInfoDTO> info_list = this->games_manager->listGames();

    std::shared_ptr<NetMessage> response = std::make_shared<NetMessageListGamesResponse>(std::move(info_list));

    this->send_queue->push(response);
}

void Reciever::run(NetMessageJoinGame* msg) {
    std::cout << "Client: " << this->client_id  << "joined to a game " << "\n";
    bool success = this->games_manager->joinGame(msg->game_room, *(this->client));
    this->game_room = msg->game_room;

    std::shared_ptr<NetMessage> response = std::make_shared<NetMessageJoinGameResponse>(success);

    this->send_queue->push(response);
}

void Reciever::run(NetMessageStartGame* msg) {
    std::cout << "starting game\n";
    this->games_manager->startGame(this->game_room);
}

void Reciever::run(NetMessageChat* msg) { }

void Reciever::run(NetMessageLeave* msg) { }

void Reciever::run(NetMessage_test* msg) { }

void Reciever::run(NetMessageInformID* msg) { }

void Reciever::run(NetMessageInitialGameState* msg_) {
    if (game_queue != nullptr) {
        game_queue->push(this->msg);
    }
}

void Reciever::run(NetMessageGameStateUpdate* msg_) {
    if (game_queue != nullptr) {
        game_queue->push(this->msg);
    }
}

void Reciever::run(NetMessageGameAction* msg_) {
    if (game_queue != nullptr) {
        game_queue->push(this->msg);
    }
}

void Reciever::run(NetMessagePlayerChangedWeapon* msg_) {
    if (game_queue != nullptr) {
        game_queue->push(this->msg);
    }
}

void Reciever::run(NetMessagePlayerChangedProjectileCountdown* msg) {
    if (game_queue != nullptr) {
        game_queue->push(this->msg);
    }
}

void Reciever::run(NetMessageGameEnded *msg) {
    // TODO
    std::cout << "Termino la partida el id ganador: " << msg->winner_client_id << std::endl;
}
