#ifndef SERVER_DUMB_CLIENT_H_
#define SERVER_DUMB_CLIENT_H_

#include "../../common_base/networking.h"

class DumbClient {
    NetChannel channel;

    public:
    explicit DumbClient(const char* serv, const char* port);

    void forward();
};

class DumbInterpreter : public NetMessageBehaviour {
    public:
    virtual void run(NetMessageChat* msg) override;
    virtual void run(NetMessage_test* msg) override;
};
#endif 
