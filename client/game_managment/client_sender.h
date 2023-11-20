#ifndef __CLIENT_SENDER_H__
#define __CLIENT_SENDER_H__

#include "queue.h"
#include "thread.h"
#include "networking.h"

#include "client_defs.h"
class ClientGameState;

class ClientSender : public Thread {
public:
    ClientSender() = delete;
    explicit ClientSender(Queue<GameEvent>& event_queue, NetChannel& net_channel);
    ~ClientSender() = default;

    ClientSender(const ClientSender& other) = delete;
    ClientSender operator=(const ClientSender& other) = delete;
    ClientSender(ClientSender&& other) = delete;
    ClientSender operator=(ClientSender&& other) = delete;

    void switch_game(ClientGameState& state);

    void run() override;
    std::shared_ptr<NetMessage> game_event_to_net_message(GameEvent event);

private:
    Queue<GameEvent>& event_queue;
    NetChannel* net_channel;
    ClientGameState* state;
};

#endif  // __CLIENT_SENDER_H__
