#ifndef COMMON_NET_MESSAGE_USER_ACTION_H_
#define COMMON_NET_MESSAGE_USER_ACTION_H_

#include <vector>
#include "net_message_dependencies.h"

enum class TipoAccion : uint8_t {
    moving_left_init,
    moving_left_end,

    moving_right_init,
    moving_right_end,

    jump_back,
    jump_foward,
};

class NetMessageUserEvent : public NetMessage {
    public:
    int client_id;
    TipoAccion tipo;
    
    NetMessageUserEvent();
    NetMessageUserEvent(const int client_id, const std::string chat);

    virtual void push_data_into(NetBuffer& container) override;
    virtual void pull_data_from(NetProtocolInterpreter& channel) override;
    virtual void execute(NetMessageBehaviour& interpreter) override;
};

class NetMessageUserShoot : public NetMessage {
    public:
    int client_id;
    float angulo;
    float carga;
    TipoProyectil proyectil;

    NetMessageUserShoot();
    NetMessageUserShoot(
        int client_id,
        float angulo,
        float carga,
        TipoProyectil proyectil
    );

    virtual void push_data_into(NetBuffer& container) override;
    virtual void pull_data_from(NetProtocolInterpreter& channel) override;
    virtual void execute(NetMessageBehaviour& interpreter) override;
};
#endif
