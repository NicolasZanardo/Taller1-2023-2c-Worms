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
            NetMessage* message = input_queue.pop();
            remove_zombies();
            message->execute(*this);

            delete(message);
        } catch (const std::exception& ex) {
            keep_running_ = false;
        }
    }
}

void WaitingLobby::stop() {
    keep_running_ = false;

    lock_guard lock(clients_mtx);
    for (auto it : clients) {
        delete(it);
    }
    clients.clear();
}

void WaitingLobby::remove_zombies() {
    std::lock_guard lock(clients_mtx);
    clients.remove_if(purged_zombie);
}

bool purged_zombie(Client* cli) {
    if (cli->is_alive())
        return false;

    delete(cli);
    return true;
}

void WaitingLobby::start_game() {
    auto game = new GameInstance(
            0.0f, -10.f, HardcodedScenarioData::get(),  // TODO GameConfig struct
            clients
            );
    game->start();
} // TODO There is no Join for now

void WaitingLobby::add(Client* new_client) {
    std::lock_guard lock(clients_mtx);
    clients.push_back(new_client);
    new_client->switch_lobby(&input_queue);
    new_client->communicate(new NetMessageInformID(new_client->id));
}

void WaitingLobby::run(NetMessageChat* msg) {
    std::lock_guard lock(clients_mtx);
    for (auto it : clients) {
        it->communicate(new NetMessageChat(msg->client_id, msg->chat));
    }
    cout << "Client " << msg->client_id << ": said:" << msg->chat << "\n";
}

void WaitingLobby::run(NetMessageLeave* msg) {
    std::lock_guard lock(clients_mtx);
    for (auto it : clients) {
        if (it->id == msg->client_id) {
            it->disconnect();
        } else {
            it->communicate(new NetMessageChat(msg->client_id, "I'm leaving."));
        }
    }
    cout << "Kicking client " << msg->client_id << "\n";
}

void WaitingLobby::run(NetMessageInformID* msg) {
    cerr << "The client " << msg->client_id << " informed their id...";
}

void WaitingLobby::run(NetMessage_test* msg) {
    cerr << "A test message was recieved...";
}
