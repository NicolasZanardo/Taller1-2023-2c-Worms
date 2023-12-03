#ifndef COMMON_NET_MESSAGE_BEHAVIOUR_H_
#define COMMON_NET_MESSAGE_BEHAVIOUR_H_

#define NET_MESSAGE_TYPE_TEST 0
#define NET_MESSAGE_TYPE_CHAT 1
#define NET_MESSAGE_TYPE_LEAVE 2
#define NET_MESSAGE_TYPE_INFORM_ID 3
#define NET_MESSAGE_TYPE_INITIAL_STATE 4
#define NET_MESSAGE_TYPE_UPDATE_STATE 5
#define NET_MESSAGE_TYPE_GAME_ACTION 6
#define NET_MESSAGE_TYPE_PLAYER_CHANGED_WEAPON 7
#define NET_MESSAGE_TYPE_PLAYER_CHANGED_PROJECTILE_COUNTDOWN 8

#define NET_MESSAGE_TYPE_CREATE_GAME 100
#define NET_MESSAGE_TYPE_CREATE_GAME_RESPONSE 101
#define NET_MESSAGE_TYPE_LIST_GAMES 102
#define NET_MESSAGE_TYPE_LIST_GAMES_RESPONSE 103
#define NET_MESSAGE_TYPE_JOIN_GAME 104
#define NET_MESSAGE_TYPE_JOIN_GAME_RESPONSE 105
#define NET_MESSAGE_TYPE_START_GAME 106

class NetMessageChat;
class NetMessageLeave;
class NetMessage_test;
class NetMessageInformID;
class NetMessageInitialGameState;
class NetMessageGameStateUpdate;
class NetMessageGameAction;
class NetMessagePlayerChangedWeapon;
class NetMessagePlayerChangedProjectileCountdown;

class NetMessageCreateGame;
class NetMessageCreateGameResponse;
class NetMessageListGames;
class NetMessageListGamesResponse;
class NetMessageJoinGame;
class NetMessageJoinGameResponse;
class NetMessageStartGame;

class NetMessageBehaviour {
public:
    virtual void run(NetMessageChat* msg) = 0;
    virtual void run(NetMessageLeave* msg) = 0;
    virtual void run(NetMessage_test* msg) = 0;
    virtual void run(NetMessageInformID* msg) = 0;
    virtual void run(NetMessageInitialGameState* msg) = 0;
    virtual void run(NetMessageGameStateUpdate* msg) = 0;
    virtual void run(NetMessageGameAction* msg) = 0;
    virtual void run(NetMessagePlayerChangedWeapon* msg) = 0;
    virtual void run(NetMessagePlayerChangedProjectileCountdown* msg) = 0;

    virtual void run(NetMessageCreateGame* msg) = 0;
    virtual void run(NetMessageCreateGameResponse* msg) = 0;
    virtual void run(NetMessageListGames* msg) = 0;
    virtual void run(NetMessageListGamesResponse* msg) = 0;
    virtual void run(NetMessageJoinGame* msg) = 0;
    virtual void run(NetMessageJoinGameResponse* msg) = 0;

    virtual void run(NetMessageStartGame* msg) = 0;

    virtual ~NetMessageBehaviour() {};
};
#endif
