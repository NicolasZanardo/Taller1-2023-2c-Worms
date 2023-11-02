#include "dumb_client.h"
#include <iostream>
using namespace std;

DumbClient::DumbClient(const char* serv, const char* port) :
    channel(std::move(Socket(serv, port)))
    {}

void DumbClient::forward() {
    NetMessage_test* msg = (NetMessage_test*)channel.read_message();
    cout << "\n\n" << msg->test_short << "\n" << msg->test_uint << "\n" << msg->test_string << "\n";
    channel.send_message(*msg);
    
    delete(msg);
}
