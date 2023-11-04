#ifndef SERVER_CLIENT_H_
#define SERVER_CLIENT_H_

#include "../../../common_base/networking.h"

class Client {
    NetChannel channel;

    public:
    const int id;
    Client(const int id, Socket skt);
    const bool is_alive() const;
    
    ~Client();
};
#endif 
