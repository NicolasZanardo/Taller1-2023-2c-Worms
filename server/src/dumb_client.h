#ifndef SERVER_DUMB_CLIENT_H_
#define SERVER_DUMB_CLIENT_H_

#include "../../common_base/networking.h"

class DumbClient {
    NetChannel channel;
    bool keep;

    public:
    DumbClient(const char* serv, const char* port);

    void forward();
    void stop();
};

class DumbInterpreter : public NetMessageBehaviour {
    DumbClient& cli;

    public:
    explicit DumbInterpreter(DumbClient& cli);
    virtual void run(NetMessageChat* msg) override;
    virtual void run(NetMessageLeave* msg) override;
    virtual void run(NetMessage_test* msg) override;
};
#endif 
