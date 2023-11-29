#ifndef SERVER_CLIENT_ACCEPTER_H_
#define SERVER_CLIENT_ACCEPTER_H_

#include "waiting_lobby.h"
#include "thread.h"
#include "networking.h"

class ClientAccepter : public Thread {
    Socket host;
    WaitingLobby& lobby;

    public:
    explicit ClientAccepter(const char* servname, WaitingLobby& lobby);

    void run() override;
    void stop() override;
};
#endif

