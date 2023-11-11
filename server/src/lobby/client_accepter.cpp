#include "client_accepter.h"
#include <utility>

ClientAccepter::ClientAccepter(const char* servname, WaitingLobby& lobby) :
    Thread(), host(servname),
    lobby(lobby)
    {}

void ClientAccepter::run() {
    int next_id = 1;
    while (keep_running_) {
        try {
            Socket skt = host.accept();
            Client* newClient = new Client(next_id++, std::move(skt));
            lobby.add(newClient);
        } catch (const std::exception& ex) {
            keep_running_ = false;
        }
    }
}

void ClientAccepter::stop() {
    keep_running_ = false;

    try {
        host.shutdown(2);
        host.close();
    } 
    catch (const std::exception& e) {}

    join();
}
