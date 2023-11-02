#include "connection_lost_exception.h"

SocketConnectionLost::SocketConnectionLost() noexcept {}
SocketConnectionLost::~SocketConnectionLost() {}

const char* SocketConnectionLost::what() const noexcept {
    return "Connection with client lost";
}
