#ifndef COMMON_NET_MESSAGE_BEHAVIOUR_H_
#define COMMON_NET_MESSAGE_BEHAVIOUR_H_

class NetMessageChat;
class NetMessageLeave;
class NetMessage_test;

class NetMessageBehaviour {
    public:
    virtual void run(NetMessageChat* msg) = 0;
    virtual void run(NetMessageLeave* msg) = 0;
    virtual void run(NetMessage_test* msg) = 0;
};
#endif
