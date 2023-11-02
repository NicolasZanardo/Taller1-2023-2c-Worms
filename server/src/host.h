#ifndef SERVER_HOST_H_
#define SERVER_HOST_H_

#include "../../common_base/networking.h"

class Host {
    Socket listener;

    public:
    explicit Host(const char* port);

    void start_lobby();
};
#endif 
