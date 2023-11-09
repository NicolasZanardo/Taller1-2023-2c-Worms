#include <iostream>
#include <stdexcept>
#include <string>

#include "src/main/server.h"
#include "src/dumb_client.h"


#define SERVER_CMND_LINE_ARGS 1

int main(int argc, char* argv[]) {
    try {
        bool testRun = false;
        bool isHost = true;
        if (argc == 3) {
            std::string action(argv[2]);
            isHost = "--testhost" == action;
            testRun = "--testclient" == action || isHost;
            
            if (!testRun) {
                std::cerr << "Bad program call. Expected "
                    << argv[0]
                    << " <puerto/servicename> [--testhost / --testclient]\n";
            }
        } else if (argc != (SERVER_CMND_LINE_ARGS + 1)) {
            std::cerr << "Bad program call. Expected "
                << argv[0]
                << " <puerto/servicename> [--testhost / --testclient]\n";
            return 1;
        }

        if (testRun) {
            std::cout << "Running test " << (isHost ? "host\n" : "client\n");
            if (isHost) {
                Server server(argv[1]);
                server.execute();
            } else {
                DumbClient cli("localhost", argv[1]);
                cli.forward();
            }
        } else {
            std::cout << "Running app\n";
            Server server(argv[1]);
            server.execute();
        }

        return 0;
    } catch (const std::exception& err) {
        std::cerr << "Something went wrong and an exception was caught: " << err.what() << "\n";
        return -1;
    } catch (...) {
        std::cerr << "Something went wrong and an unknown exception was caught.\n";
        return -1;
    }
}
