#include "client_request.h"

//==============================================================================
ClientRequestCreateGame::ClientRequestCreateGame(const std::string& room_name)
    : room_name(room_name), num_worms(num_worms) {}

void ClientRequestCreateGame::execute(Protocol& protocol) {
    // protocol.createGame(this->room_name, this->num_worms);
}

//==============================================================================
ClientRequestJoinGame::ClientRequestJoinGame(const std::string& room_name)
    : room_name(room_name) {}

void ClientRequestJoinGame::execute(Protocol& protocol) {
    // protocol.joinGame(this->room_name);
}

//==============================================================================
void ClientRequestLeaveGame::execute(Protocol& protocol) {
    // protocol.leaveGame();
}

//==============================================================================
ClientRequestSendGameCommand::ClientRequestSendGameCommand(/*command*/)
    // : command(command)
    {}

void ClientRequestSendGameCommand::execute(Protocol& protocol) {
    // protocol.sendGameCommand(command);
}
