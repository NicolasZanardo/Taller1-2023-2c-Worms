#include "launcher.h"

#include <QApplication>

#include <stdexcept>
#include <string>

#include "../client.h"

#include "launcher/client_lobby_settings.h"
#include "networking.h"

#define CLIENT_CMND_LINE_ARGS 2
#define CLIENT_MSG_ERROR_NUM_CLARGS "Invalid numbers of arguments."

int main(int argc, char* argv[]) {
    try {
        if (argc != (CLIENT_CMND_LINE_ARGS + 1)) {
            std::cerr << CLIENT_MSG_ERROR_NUM_CLARGS << '\n';
            return 1;
        }

        // DumbClient client(argv[1], argv[2]);
        // client.start();

        NetChannel net_channel(argv[1], argv[2]);
        ClientLobbySettings lobby_settings;

        std::unique_ptr<NetMessage> received_id_msg(net_channel.read_message());
        received_id_msg->execute(lobby_settings);

        // Qt.
        QApplication a(argc, argv);
        Launcher w(net_channel, lobby_settings);
        w.show();
        a.exec();

        // SDL.
        Client client(net_channel, lobby_settings);
        client.execute();

        return 0;
    } catch (const std::exception& err) {
        std::cerr << "Something went wrong and an exception was caught: " << err.what() << "\n";
        return -1;
    } catch (...) {
        std::cerr << "Something went wrong and an unknown exception was caught.\n";
        return -1;
    }
}
