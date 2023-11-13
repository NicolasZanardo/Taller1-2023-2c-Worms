#include "waiting_lobby.h"
#include <exception>
#include <iostream>

using namespace std;
bool purged_zombie(Client* cli);

WaitingLobby::WaitingLobby() :
    Thread(), clients_mtx(),
    clients(), input_queue(60)
    {}

void WaitingLobby::run() {
    while (keep_running_) {
        try {
            return;
            auto message = input_queue.pop();
            remove_zombies();
            message->execute(*this);
        } catch (const std::exception& ex) {
            keep_running_ = false;
        }
    }
}

void WaitingLobby::stop() {
    keep_running_ = false;
    input_queue.close();
    join();

    lock_guard lock(clients_mtx);
    for (auto it : clients) {
        delete(it);
    }
    clients.clear();
}

void WaitingLobby::remove_zombies() {
    lock_guard lock(clients_mtx);
    clients.remove_if(purged_zombie);
}

bool purged_zombie(Client* cli) {
    if (cli->is_alive())
        return false;

    delete(cli);
    return true;
}

GameEngineInstance* WaitingLobby::start_game() {
    auto game = new GameEngineInstance(
            0.0f, -10.f, HardcodedScenarioData::get(),  // TODO GameConfig struct
            clients
            );
    game->start();
    
    return game;
} // TODO There is no Join for now

void WaitingLobby::add(Client* new_client) {
    lock_guard lock(clients_mtx);
    clients.push_back(new_client);
    new_client->switch_lobby(&input_queue);
    std::shared_ptr<NetMessage> net_message(new NetMessageInformID(new_client->id));
    new_client->communicate(net_message);

    cout << "The client " << new_client->id << " just connected.\n";
}

void WaitingLobby::run(NetMessageChat* msg) {
    lock_guard lock(clients_mtx);
    std::shared_ptr<NetMessage> net_message(new NetMessageChat(msg->client_id, msg->chat));

    for (auto it : clients) {
        it->communicate(net_message);
    }
    cout << "Client " << msg->client_id << ": said: " << msg->chat << ".\n";
}

void WaitingLobby::run(NetMessageLeave* msg) {
    lock_guard lock(clients_mtx);
    std::shared_ptr<NetMessage> net_message(new NetMessageChat(msg->client_id, "I'm leaving."));

    for (auto it : clients) {
        if (it->id == msg->client_id) {
            it->disconnect();
        } else {
            it->communicate(net_message);
        }
    }
    cout << "Kicking client " << msg->client_id << ".\n";
}

void WaitingLobby::run(NetMessageInformID* msg) {
    cout << "ERROR: The client " << msg->client_id << " informed their id...";
}

void WaitingLobby::run(NetMessage_test* msg) {
    cout << "ERROR: A test message was recieved...";
}

void WaitingLobby::run(NetMessageInitialGameState* msg) {
    cout << "ERROR: Shouldnt receive MessageInitialState...";
}

void WaitingLobby::run(NetMessageGameStateUpdate* msg) {
    cout << "ERROR: Shouldnt receive MessageGameUpdate...";
}

void WaitingLobby::run(NetMessageGameAction* msg) {
    cerr << "Error: received action in lobby..";
}
