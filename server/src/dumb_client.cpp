#include "dumb_client.h"
#include <iostream>
using namespace std;

DumbClient::DumbClient(const char* serv, const char* port) :
    channel(std::move(Socket(serv, port))),
    keep(true)
    {}

void DumbClient::forward() {
    DumbInterpreter interpreter(*this);

    while (keep)
    {
        NetMessage* msg = channel.read_message();
        msg->execute(interpreter);
        delete(msg);
    }
}

void DumbClient::stop() {
    keep = false;
}

DumbInterpreter::DumbInterpreter(DumbClient& cli) : cli(cli) {}

void DumbInterpreter::run(NetMessageChat* msg) {
    cout << "Client " << msg->client_id << " said: " << msg->chat << "\n";
}

void DumbInterpreter::run(NetMessageLeave* msg) {
    cli.stop();
    cout << "Bye\n";
}


void DumbInterpreter::run(NetMessage_test* msg) {
    cout << "short: " << msg->test_short << " uint: " << msg->test_uint << " string: " << msg->test_string << "\n";
}
