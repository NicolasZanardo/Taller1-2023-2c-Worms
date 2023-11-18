#ifndef __CLIENT_REQUEST_H__
#define __CLIENT_REQUEST_H__

#include <string>

// #include "protocol.h"

//==============================================================================
class ClientRequest {
public:
    ClientRequest() = default;
    virtual ~ClientRequest() = default;

    // virtual void execute(Protocol& protocol) = 0;
};

//==============================================================================
class ClientRequestCreateGame: public ClientRequest {
public:
    ClientRequestCreateGame() = delete;
    explicit ClientRequestCreateGame(const std::string& room_name, uint16_t num_worms);
    virtual ~ClientRequestCreateGame() = default;

    // void execute(Protocol& protocol) override;

private:
    std::string room_name;
    uint16_t num_worms;
};

//==============================================================================
class ClientRequestJoinGame: public ClientRequest {
public:
    ClientRequestJoinGame() = delete;
    explicit ClientRequestJoinGame(const std::string& room_name);
    virtual ~ClientRequestJoinGame() = default;

    // void execute(Protocol& protocol) override;

private:
    std::string room_name;
};

//==============================================================================
class ClientRequestLeaveGame : public ClientRequest {
public:
    ClientRequestLeaveGame() = default;
    virtual ~ClientRequestLeaveGame() = default;

    // void execute(Protocol& protocol) override;
};

//==============================================================================
class ClientRequestSendGameCommand : public ClientRequest {
    ClientRequestSendGameCommand() = delete;
    explicit ClientRequestSendGameCommand(/*command*/);

    // void execute(Protocol& protocol) override;

private:
    /*command*/
};

#endif  // __CLIENT_ACTIONS_H__