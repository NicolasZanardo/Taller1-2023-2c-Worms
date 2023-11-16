#ifndef __CLIENT_RECEIVER_H__
#define __CLIENT_RECEIVER_H__

#include <memory>
#include "queue.h"
#include "thread.h"
#include "networking.h"

#include "client_game_state_dto.h"
#include "client_defs.h"

class ClientReceiver : public Thread, public NetMessageBehaviour {
public:
    ClientReceiver() = delete;
    // explicit ClientReceiver(Queue<GameEvent>& state_queue, Queue<GameEvent>& echo_queue);
    // explicit ClientReceiver(Queue<GameEvent>& state_queue, NetChannel& net_channel);
    explicit ClientReceiver(Queue<std::shared_ptr<ClientGameStateDTO>>& state_queue, NetChannel& net_channel);
    ~ClientReceiver() = default;

    ClientReceiver(const ClientReceiver& other) = delete;
    ClientReceiver operator=(const ClientReceiver& other) = delete;
    ClientReceiver(ClientReceiver&& other) = delete;
    ClientReceiver operator=(ClientReceiver&& other) = delete;

    void run() override;

    void run(NetMessageChat* msg) override;
    void run(NetMessageLeave* msg) override;
    void run(NetMessage_test* msg) override;
    void run(NetMessageInformID* msg) override;
    void run(NetMessageInitialGameState* msg) override;
    void run(NetMessageGameStateUpdate* msg) override;
    void run(NetMessageGameAction* msg) override;

private:
    // Queue<GameEvent>& state_queue;
    Queue<std::shared_ptr<ClientGameStateDTO>>& state_queue;


    // Queue<GameEvent>& echo_queue;

    NetChannel* net_channel;
};

#endif  // __CLIENT_RECEIVER_H__