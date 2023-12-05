#ifndef CLIENT_CLIENT_RECEIVER_H_
#define CLIENT_CLIENT_RECEIVER_H_

#include <memory>
#include "queue.h"
#include "thread.h"
#include "networking.h"

#include "client_game_state_dto.h"
class ClientGameState;

class ClientReceiver : public Thread, public NetMessageBehaviour {
public:
    ClientReceiver(Queue<std::shared_ptr<ClientGameStateDTO>>& state_queue, NetChannel& net_channel);
    ClientReceiver() = delete;
    ~ClientReceiver() = default;

    ClientReceiver(const ClientReceiver& other) = delete;
    ClientReceiver operator=(const ClientReceiver& other) = delete;
    ClientReceiver(ClientReceiver&& other) = delete;
    ClientReceiver operator=(ClientReceiver&& other) = delete;

    void switch_game(ClientGameState& state);

    void run() override;

    void run(NetMessageChat* msg) override;
    void run(NetMessageLeave* msg) override;
    void run(NetMessage_test* msg) override;
    void run(NetMessageInformID* msg) override;
    void run(NetMessageInitialGameState* msg) override;
    void run(NetMessageGameStateUpdate* msg) override;
    void run(NetMessageGameAction* msg) override;
    void run(NetMessagePlayerChangedWeapon* msg) override;
    void run(NetMessagePlayerChangedProjectileCountdown* msg) override;
    void run(NetMessageGameEnded* msg) override;

    void run(NetMessageCreateGame* msg) override { }
    void run(NetMessageListGames* msg) override { }
    void run(NetMessageJoinGame* msg) override { }

    void run(NetMessageCreateGameResponse* msg) override {}
    void run(NetMessageJoinGameResponse* msg) override {}
    void run(NetMessageListGamesResponse* msg) override {}

    void run(NetMessageStartGame* msg) override {}

private:
    Queue<std::shared_ptr<ClientGameStateDTO>>& state_queue;
    NetChannel* net_channel;
    ClientGameState* state;
};

#endif  // __CLIENT_RECEIVER_H__