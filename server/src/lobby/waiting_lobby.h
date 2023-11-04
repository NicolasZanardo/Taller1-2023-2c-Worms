#ifndef SERVER_WAITING_LOBBY_H_
#define SERVER_WAITING_LOBBY_H_

#include <list>
#include <string>
#include "../../../common_base/networking.h"
#include "../../../common_base/thread.h"

class WaitingLobby : public Thread {
    Socket host;
    std::list<NetChannel*> clients;

    public:
    explicit WaitingLobby(const char* servname);

    void run() override;
    void stop() override;
};
#endif
