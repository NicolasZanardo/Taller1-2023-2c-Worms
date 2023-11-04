#include "waiting_lobby.h"
#include <exception>
#include <iostream>

WaitingLobby::WaitingLobby(const char* servname) :
    Thread(), host(servname)
    {}

void WaitingLobby::run() {
    while (keep_running_) {
        try {
            std::cout << "Listening for clients.\n";
            NetChannel* channel = new NetChannel(host.accept());
        } catch (const std::exception& ex) {
            keep_running_ = false;
        }
    }
}

void WaitingLobby::stop() {
    keep_running_ = false;

    try {
        host.shutdown(2);
        host.close();
    } 
    catch (const std::exception& e) {}
}
