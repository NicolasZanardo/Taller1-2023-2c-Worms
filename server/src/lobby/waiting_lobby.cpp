#include "waiting_lobby.h"
#include <exception>
#include <iostream>
using namespace std;

WaitingLobby::WaitingLobby(const char* servname) :
    Thread(), 
    host(servname),
    clients_mtx(),
    clients()
    {}

void WaitingLobby::run() {
    int next_id = 1;
    while (keep_running_) {
        try {
            Client* newClient = new Client(next_id++, host.accept());
            clients.push_back(newClient);

            cout << "Joined client: " << newClient->id << ".\n";

            remove_zombies();
        } catch (const std::exception& ex) {
            keep_running_ = false;
        }
    }
}

void WaitingLobby::stop() {
    keep_running_ = false;

    try {
        host.shutdown(2);
        host.close();
    } 
    catch (const std::exception& e) {}

    std::lock_guard lock(clients_mtx);
    for (auto it : clients) {
        delete(it);
    }
    clients.clear();
}

void WaitingLobby::kick(const int client_id) {
    std::lock_guard lock(clients_mtx);

    Client* instance = nullptr;
    for (auto it : clients) {
        if (it->id == client_id)
            instance = it;
    }

    clients.remove(instance);
    delete(instance);
}

bool purged_zombie(Client* cli);
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
