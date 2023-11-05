#include "dumb_client.h"
#include <iostream>
using namespace std;

DumbClient::DumbClient(const char* serv, const char* port) :
    channel(std::move(Socket(serv, port)))
    {}

void DumbClient::forward() {
    DumbInterpreter interpreter;
    NetMessage* msg = channel.read_message();
    msg->execute(interpreter);

    //channel.send_message(*msg);
    
    delete(msg);
}

void DumbInterpreter::run(NetMessageChat* msg) {
    cout << "Client " << msg->client_id << " said: " << msg->chat << "\n";
}

void DumbInterpreter::run(NetMessage_test* msg) {
    cout << "short: " << msg->test_short << " uint: " << msg->test_uint << " string: " << msg->test_string << "\n";
}
