#include "InGameClients.h"

InGameClients::InGameClients(const std::list<Client *> &clients): clients() {
    for (const auto &client: clients) {
        this->clients.emplace(client->id, client);
    }
}

size_t InGameClients::size(){
    return clients.size();
}

void InGameClients::send(size_t clientId, std::shared_ptr<NetMessage> msg) {
    clients[clientId]->communicate(msg);
}

void InGameClients::send_all(std::shared_ptr<NetMessage> msg) {
    for (const auto &[id, client]: clients) {
        client->communicate(msg);
    }
}

void InGameClients::remove(size_t clientId) {
    for (auto [id, client]: clients) {
        if (id == clientId) {
            client->disconnect();
        } else {
            client->communicate(std::shared_ptr<NetMessage>(new NetMessageChat(clientId, "I'm leaving.")));
        }
    }
}