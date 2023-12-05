#include "game_room.h"

#include <stdexcept>

#include "../client/client.h"  // Del server.
#include "../game/scenario/HardcodedScenarioData.h"
#include "GameEngineInstance.h"

GameRoom::GameRoom()
    : was_ended(false) {}

GameRoom::GameRoom(const std::string& name, const std::string& scenario, uint8_t total_pĺayers)
    : name(name)
    , scenario(scenario)
    , total_players(total_pĺayers) {}

void GameRoom::join(Client& client) {
    if (this->players.find(client.getID()) != this->players.end()) {
        throw std::runtime_error("This id was alredy joined.\n");
    }

    this->players.emplace(client.getID(), client);
    this->list_clients.push_back(&client);
}

void GameRoom::leave(Client& client) {
    if (this->players.find(client.getID()) == this->players.end()) {
        throw std::runtime_error("This id was not joined.\n");
    }

    this->players.erase(client.getID());
}

void GameRoom::start() {
    std::cout << "Starting game ...\n";
    
    this->game_instance = new GameEngineInstance(
            0, -40, HardcodedScenarioData::get(),  // TODO GameConfig struct
            this->list_clients
            );


    this->game_instance->start();
}

GameInfoDTO GameRoom::getInfo() const {
    return std::move(GameInfoDTO(this->name, this->scenario, this->total_players, this->players.size()));
}
