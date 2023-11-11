#ifndef COMMON_NET_MESSAGE_USER_ACTION_H_
#define COMMON_NET_MESSAGE_USER_ACTION_H_

#include <vector>
#include "net_message_dependencies.h"
#include "../../Game/ActionTypeDto.h"

class NetMessageUserAction : public NetMessage {
    public:
    int client_id;


    NetMessageUserAction();
    NetMessageUserAction(const int client_id, const ActionTypeDto& action);

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
