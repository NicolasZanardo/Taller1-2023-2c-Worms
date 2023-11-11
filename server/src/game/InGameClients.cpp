#include "InGameClients.h"

InGameClients::InGameClients(const std::list<Client *> &clients): clients() {
    for (const auto &client: clients) {
        this->clients.emplace(client->id, client);
    }
}

size_t InGameClients::size(){
    return clients.size();
}

void InGameClients::send(size_t clientId, NetMessage* msg) {
    clients[clientId]->communicate(msg);
}

void InGameClients::sendAll(NetMessage* msg) {
    // Iterate and send it to every client
    for (const auto &[id, client]: clients) {
        client->communicate(msg);
    }
}

void InGameClients::remove(size_t clientId) {
    for (auto [id, client]: clients) {
        if (id == clientId) {
            client->disconnect();
        } else {
            client->communicate(new NetMessageChat(clientId, "I'm leaving."));
        }
    }
}