#include "dumb_client.h"
#include <iostream>
#include <memory>
#include <utility>
using namespace std;

DumbClient::DumbClient(const char* serv, const char* port) :
    keep(true), channel(std::move(Socket(serv, port))),
    interpreter(new DumbInterpreter(*this))
    {}

DumbClient::~DumbClient() {
    delete(interpreter);
}

void DumbClient::forward() {
    try {
        while (keep) {
            auto msg = channel.read_message();
            msg->execute(*interpreter);
            delete(msg);
        }
    } catch (...) {
        cout << "Exception thrown.\n";
    }
}

void DumbClient::stop() {
    keep = false;
    channel.dissconect();
}

DumbInterpreter::DumbInterpreter(DumbClient& cli) : cli(cli) {}

void DumbInterpreter::run(NetMessageChat* msg) {
    cout << "Client " << msg->client_id << " said: " << msg->chat << "\n";
}

void DumbInterpreter::run(NetMessageLeave* msg) {
    cli.stop();
    cout << "Bye\n";
}

void DumbInterpreter::run(NetMessageInformID* msg) {
    cout << "I AM CLIENT "<< msg->client_id << "\n";
}

void DumbInterpreter::run(NetMessage_test* msg) {
    cout << "short: " << msg->test_short << " uint: " << msg->test_uint << " string: " << msg->test_string << "\n";
}

void DumbInterpreter::run(NetMessageInitialGameState* msg) {
    cout << "width: " << msg->room_width << " height: " << msg->room_height << " amount of beams on map: " << msg->beams.size() << "\n";
}

void DumbInterpreter::run(NetMessageGameStateUpdate* msg) {
    cout << "active worm id: " << msg->id_active_entity << "\n"; //<< " height: " << msg->room_height << " amount of beams on map: " << msg->beams.size() << "\n";
}

void DumbInterpreter::run(NetMessageGameAction* msg) {
    // Client shouldnt receive
    cout << "action for worm id: " << msg->client_id << "\n"; //<< " height: " << msg->room_height << " amount of beams on map: " << msg->beams.size() << "\n";
}
