#ifndef __CLIENT_RECEIVER_H__
#define __CLIENT_RECEIVER_H__

#include "queue.h"
#include "thread.h"

#include "client_defs.h"

class ClientReceiver : public Thread {
public:
    ClientReceiver() = delete;
    explicit ClientReceiver(Queue<GameEvent>& state_queue, Queue<GameEvent>& echo_queue);
    ~ClientReceiver() = default;

    ClientReceiver(const ClientReceiver& other) = delete;
    ClientReceiver operator=(const ClientReceiver& other) = delete;
    ClientReceiver(ClientReceiver&& other) = delete;
    ClientReceiver operator=(ClientReceiver&& other) = delete;

    void run() override;

private:
    Queue<GameEvent>& state_queue;
    Queue<GameEvent>& echo_queue;
};

#endif  // __CLIENT_RECEIVER_H__