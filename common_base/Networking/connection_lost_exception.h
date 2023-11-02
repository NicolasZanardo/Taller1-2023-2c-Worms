#ifndef CONNECTION_LOST_EXCEPTION_H_
#define CONNECTION_LOST_EXCEPTION_H_

#include <exception>

class SocketConnectionLost : public std::exception {
    public:
    SocketConnectionLost() noexcept;
    virtual const char* what() const noexcept;
    virtual ~SocketConnectionLost();
};

#endif
