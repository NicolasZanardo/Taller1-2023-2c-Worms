#include <iostream>
#include <stdexcept>
#include <string>

#include "client_lobby.h"
#include "client_lobby_settings.h"

#define CLIENT_CMND_LINE_ARGS 2
#define CLIENT_MSG_ERROR_NUM_CLARGS "Invalid numbers of arguments."

int main(int argc, char* argv[]) {
    try {
        if (argc != (CLIENT_CMND_LINE_ARGS + 1)) {
            std::cerr << CLIENT_MSG_ERROR_NUM_CLARGS << '\n';
            return 1;
        }
        
        ClientLobbySettings lobby_settings;
        ClientLobby client_lobby(argv[1], argv[2], lobby_settings);
        client_lobby.execute();

        return 0;
    } catch (const std::exception& err) {
        std::cerr << "Something went wrong and an exception was caught: " << err.what() << "\n";
        return -1;
    } catch (...) {
        std::cerr << "Something went wrong and an unknown exception was caught.\n";
        return -1;
    }
}