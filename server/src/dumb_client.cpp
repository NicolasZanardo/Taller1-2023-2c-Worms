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

void DumbClient::start() {
    std::thread receiveThread(&DumbClient::forward, this);
    std::thread sendThread(&DumbClient::send_messages, this);

    receiveThread.join();
    sendThread.join();
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

void DumbClient::send_messages() {
    while (keep) {
        std::string user_input;
        std::getline(std::cin, user_input);

        if (user_input == "exit") {
            stop();
            break;
        }

        if (user_input == "Move right") {
            NetMessageGameAction msg(1, ActionTypeDto::moving_right_init);
            channel.send_message(msg);
        } else if (user_input == "Move left") {
            NetMessageGameAction msg(1, ActionTypeDto::moving_left_init);
            channel.send_message(msg);
        } else if (user_input == "Stop move") {
            NetMessageGameAction msg(1, ActionTypeDto::stop_moving);
            channel.send_message(msg);
        } else if (user_input == "Jump f") {
            NetMessageGameAction msg(1, ActionTypeDto::jump_forward);
            channel.send_message(msg);
        } else if (user_input == "Jump b") {
            NetMessageGameAction msg(1, ActionTypeDto::jump_back);
            channel.send_message(msg);
        }

        // Simulate some delay between checking for console input
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}


void DumbClient::stop() {
    {
        std::lock_guard<std::mutex> lock(mutex_);
        keep = false;
    }
    condition_variable_.notify_all();
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
    cout << "short: " << msg->test_short << " uint: " << msg->test_uint << " float: " << msg->test_float << " string: " << msg->test_string << "\n";
}

void DumbInterpreter::run(NetMessageInitialGameState* msg) {
    cout << "width: " << msg->room_width << " height: " << msg->room_height << " amount of beams on map: " << msg->beams.size() << "\n";
}

void DumbInterpreter::run(NetMessageGameStateUpdate* msg) {
    // cout << "Its turn of client id: " << msg->active_client_id << " and its current worm id is: " << msg->active_entity_id << "\n"; //<< " height: " << msg->room_height << " amount of beams on map: " << msg->beams.size() << "\n";
}

void DumbInterpreter::run(NetMessageGameAction* msg) {
    // Client shouldnt receive
    cout << "action for worm id: " << msg->client_id << "\n"; //<< " height: " << msg->room_height << " amount of beams on map: " << msg->beams.size() << "\n";
}
