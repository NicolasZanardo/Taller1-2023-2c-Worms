#ifndef SERVER_INGAMECLIENTS_H
#define SERVER_INGAMECLIENTS_H

#include <unordered_map>
#include <list>
#include "client.h"

class InGameClients {

    std::unordered_map<size_t, Client*> clients;

public:
    explicit InGameClients(const std::list<Client*>& clients);

    void sendAll(std::shared_ptr<NetMessage> msg);
    void send(size_t clientId, std::shared_ptr<NetMessage> msg);

    size_t size();

    void remove(size_t clientId);
};


#endif
