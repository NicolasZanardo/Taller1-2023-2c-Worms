#include <iostream>
#include <stdexcept>
#include <string>

#include "server.h"

#define SERVER_CMND_LINE_ARGS 1

int main(int argc, char* argv[]) {
    try {
        if (argc != (SERVER_CMND_LINE_ARGS + 1)) {
            std::cerr << "Bad program call. Expected "
                << argv[0]
                << " <puerto/servicename>\n";
            return 1;
        }

        Server server(argv[1]);
        server.execute();

        return 0;
    } catch (const std::exception& err) {
        std::cerr << "Something went wrong and an exception was caught: " << err.what() << "\n";
        return -1;
    } catch (...) {
        std::cerr << "Something went wrong and an unknown exception was caught.\n";
        return -1;
    }
}
