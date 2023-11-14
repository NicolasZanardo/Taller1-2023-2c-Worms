#ifndef __CLIENT_REQUEST_H__
#define __CLIENT_REQUEST_H__

#include "client_defs.h"

class Protocol;

//==============================================================================
class ClientRequest {
public:
    ClientRequest() = default;
    virtual ~ClientRequest() = default;

    virtual void send() = 0;
};


//==============================================================================
class ClientRequestGameEvent : public ClientRequest {
public:
    ClientRequestGameEvent() = delete;
    explicit ClientRequestGameEvent(GameEvent game_event);
    virtual ~ClientRequestGameEvent() =  default;

    void send() override;

private:
    GameEvent game_event;
};



#endif  // _CLIENT_REQUEST_H__
