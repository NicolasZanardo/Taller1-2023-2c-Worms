#ifndef __CLIENT_SENDER_H__
#define __CLIENT_SENDER_H__

#include "queue.h"
#include "thread.h"
#include "networking.h"

#include "client_defs.h"

class ClientSender : public Thread {
public:
    ClientSender() = delete;
    explicit ClientSender(Queue<GameEvent>& event_queue, Queue<GameEvent>& echo_queue);
    ~ClientSender() = default;

    ClientSender(const ClientSender& other) = delete;
    ClientSender operator=(const ClientSender& other) = delete;
    ClientSender(ClientSender&& other) = delete;
    ClientSender operator=(ClientSender&& other) = delete;

    void run() override;

private:
    Queue<GameEvent>& event_queue;
    Queue<GameEvent>& echo_queue;
};

#endif  // __CLIENT_SENDER_H__
