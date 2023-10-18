#ifndef __SERVER_H__
#define __SERVER_H__

class Server {
public:
    Server() = delete;
    explicit Server(const char* service_name);
    ~Server() = default;

    Server(const Server& other) = delete;
    Server& operator=(const Server& other) = delete;

    Server(Server&& other) = delete;
    Server& operator=(Server&& other) = delete;

    void execute();
};

#endif  // __SERVER_H__
