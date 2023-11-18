#ifndef __CLIENT_SENDER_H__
#define __CLIENT_SENDER_H__

#include "queue.h"
#include "thread.h"
#include "networking.h"

#include "client_defs.h"

class ClientSender : public Thread {
public:
    ClientSender() = delete;
    explicit ClientSender(Queue<GameEvent>& event_queue, NetChannel& net_channel);
    ~ClientSender() = default;

    ClientSender(const ClientSender& other) = delete;
    ClientSender operator=(const ClientSender& other) = delete;
    ClientSender(ClientSender&& other) = delete;
    ClientSender operator=(ClientSender&& other) = delete;

    void run() override;
    std::shared_ptr<NetMessage> game_event_to_net_message(GameEvent& event);

private:
    int client_id = 1; // TODO GET FROM SERVER
    Queue<GameEvent>& event_queue;
    NetChannel* net_channel;
};

#endif  // __CLIENT_SENDER_H__
