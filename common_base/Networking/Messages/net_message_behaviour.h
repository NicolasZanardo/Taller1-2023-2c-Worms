#ifndef COMMON_NET_MESSAGE_BEHAVIOUR_H_
#define COMMON_NET_MESSAGE_BEHAVIOUR_H_

#define NET_MESSAGE_TYPE_TEST 0
#define NET_MESSAGE_TYPE_CHAT 1
#define NET_MESSAGE_TYPE_LEAVE 2
#define NET_MESSAGE_TYPE_INFORM_ID 3
#define NET_MESSAGE_TYPE_INITIAL_STATE 4
#define NET_MESSAGE_TYPE_UPDATE_STATE 5
#define NET_MESSAGE_TYPE_GAME_ACTION 6
#define NET_MESSAGE_TYPE_PLAYER_SHOT 7

class NetMessageChat;
class NetMessageLeave;
class NetMessage_test;
class NetMessageInformID;
class NetMessageInitialGameState;
class NetMessageGameStateUpdate;
class NetMessageGameAction;
class NetMessagePlayerShot;

class NetMessageBehaviour {
    public:
    virtual void run(NetMessageChat* msg) = 0;
    virtual void run(NetMessageLeave* msg) = 0;
    virtual void run(NetMessage_test* msg) = 0;
    virtual void run(NetMessageInformID* msg) = 0;
    virtual void run(NetMessageInitialGameState* msg) = 0;
    virtual void run(NetMessageGameStateUpdate* msg) = 0;
    virtual void run(NetMessageGameAction* msg) = 0;
    virtual void run(NetMessagePlayerShot* msg) = 0;

    virtual ~NetMessageBehaviour() {};
};
#endif
