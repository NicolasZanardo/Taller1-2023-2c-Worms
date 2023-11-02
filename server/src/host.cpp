#include "host.h"
#include <iostream>
using namespace std;

Host::Host(const char* port) :
    listener(port)
    {}

void Host::start_lobby() {
    NetChannel channel(listener.accept());
    
    NetMessage_test msg;
    msg.test_short = 12;
    msg.test_uint = 1231;
    msg.test_string = "new test string";

    channel.send_message(msg);
    NetMessage_test* sameMsg = (NetMessage_test*)channel.read_message();

    cout << "\n\n" << sameMsg->test_short << "\n" << sameMsg->test_uint << "\n" << sameMsg->test_string << "\n";

    delete(sameMsg);
}
