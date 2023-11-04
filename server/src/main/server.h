#ifndef __SERVER_H__
#define __SERVER_H__

class Server {
    const char* servname;
public:
    explicit Server(const char* servname);
    void execute();
    void test_isHost(bool isHost);

private:
    Server() = delete;
    Server(const Server& other) = delete;
    Server& operator=(const Server& other) = delete;
    Server(Server&& other) = delete;
    Server& operator=(Server&& other) = delete;
};

#endif  // __SERVER_H__
