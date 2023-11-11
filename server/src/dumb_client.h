#ifndef SERVER_DUMB_CLIENT_H_
#define SERVER_DUMB_CLIENT_H_

#include "../../common_base/networking.h"
class DumbInterpreter;

class DumbClient {
    bool keep;
    NetChannel channel;
    DumbInterpreter* interpreter;

    public:
    DumbClient(const char* serv, const char* port);
    ~DumbClient();

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
    virtual void run(NetMessageInformID* msg) override;
    virtual void run(NetMessageInitialGameState* msg) override;
    virtual void run(NetMessageGameStateUpdate* msg) override;
};
#endif 
