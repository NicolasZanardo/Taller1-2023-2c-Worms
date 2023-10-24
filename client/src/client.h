#ifndef __CLIENT_H__
#define __CLIENT_H__

class Client {
public:
    Client() = delete;
    explicit Client(const char* host_name, const char* service_name);
    ~Client() = default;

    Client(const Client& other) = delete;
    Client& operator=(const Client& other) = delete;

    Client(Client&& other) = delete;
    Client& operator=(Client&& other) = delete;

    void execute();
};

#endif  // __CLIENT_H__
