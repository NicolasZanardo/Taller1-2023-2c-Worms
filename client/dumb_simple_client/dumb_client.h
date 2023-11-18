#ifndef CLIENT_DUMB_CLIENT_H_
#define CLIENT_DUMB_CLIENT_H_

#include <SDL2pp/SDL2pp.hh>
#include "../../common_base/networking.h"
#include "../game_ui/sprites_manager.h"
#include "dumb_stage.h"
class DumbInterpreter;

class DumbClient {
    bool keep;
    NetChannel channel;
    DumbInterpreter* interpreter;
    std::mutex mutex_;
    std::condition_variable condition_variable_;
    std::queue<std::string> messages;
    std::queue<std::string> console_input;

    bool initialized = false;
    TheStage* stage;
    SpritesManager* sprites_manager;

    public:
    DumbClient(const char* serv, const char* port);
    ~DumbClient();

    void start();
    void stop();
    void forward();
    void send_messages();

    friend class DumbInterpreter;
};

class DumbInterpreter : public NetMessageBehaviour {
    DumbClient& cli;

    public:
    SDL2pp::Renderer* renderer;
    explicit DumbInterpreter(DumbClient& cli);
    virtual void run(NetMessageChat* msg) override;
    virtual void run(NetMessageLeave* msg) override;
    virtual void run(NetMessage_test* msg) override;
    virtual void run(NetMessageInformID* msg) override;
    virtual void run(NetMessageInitialGameState* msg) override;
    virtual void run(NetMessageGameStateUpdate* msg) override;
    virtual void run(NetMessageGameAction* msg) override;

    ~DumbInterpreter() {}
};
#endif 
