#include "server_client_accepter.h"
#include "server_client.h"

#include <utility>

ClientAccepter::ClientAccepter(const char* servname, WaitingLobby& lobby, GamesManager& games_manager)
    : Thread()
    , host(servname)
    , lobby(lobby)
    , games_manager(&games_manager) {}

ClientAccepter::~ClientAccepter() {
    this->lobby.removeAll();
}

void ClientAccepter::run() {
    int next_id = 1;

    while (Thread::keep_running_) {
        try {
            // Client* newClient = new Client(next_id++, std::move(skt), *(this->games_manager));
            // lobby.add(newClient);

            Socket skt = host.accept();
            this->lobby.removeZombies();
            this->lobby.addClient(next_id++, std::move(skt), *(this->games_manager));
        } catch (const std::exception& ex) {
            Thread::keep_running_ = false;
        }
    }
}

void ClientAccepter::stop() {
    Thread::keep_running_ = false;

    try {
        host.shutdown(2);
        host.close();
    } catch (const std::exception& e) {}

    Thread::join();
}
