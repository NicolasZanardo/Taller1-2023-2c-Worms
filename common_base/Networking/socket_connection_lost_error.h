#ifndef CONNECTION_LOST_EXCEPTION_H_
#define CONNECTION_LOST_EXCEPTION_H_

#include <exception>
#include "net_channel.h"
class Socket;

class SocketConnectionLost : public std::exception {
    const Socket* instance;

    public:
    explicit SocketConnectionLost(const Socket*) noexcept;
    virtual ~SocketConnectionLost();
    
    virtual const char* what() const noexcept override;
    const bool was(const Socket*) const  noexcept;
    const bool was(const NetChannel*) const noexcept;
};

#endif
