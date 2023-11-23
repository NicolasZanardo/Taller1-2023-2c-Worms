#ifndef SERVER_DUMB_CLIENT_H_
#define SERVER_DUMB_CLIENT_H_

#include "../../common_base/networking.h"
class DumbInterpreter;

class DumbClient {
    bool keep;
    NetChannel channel;
    DumbInterpreter* interpreter;
    std::mutex mutex_;
    std::condition_variable condition_variable_;
    std::queue<std::string> messages;
    std::queue<std::string> console_input;

    public:
    DumbClient(const char* serv, const char* port);
    ~DumbClient();

    void start();
    void stop();
    void forward();
    void send_messages();
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
    virtual void run(NetMessageGameAction* msg) override;
    virtual void run(NetMessagePlayerChangedWeapon* msg) override;

    ~DumbInterpreter() {}
};
#endif 
