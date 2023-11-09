#ifndef COMMON_NET_MESSAGE_INITIAL_GAME_SATE_H_
#define COMMON_NET_MESSAGE_INITIAL_GAME_SATE_H_

#include <vector>
#include "net_message_dependencies.h"

enum class TipoViga : uint8_t {
    viga_corta = 0x00,
    viga_larga = 0x01
};

enum class TipoEscenario : uint8_t {
    por_defecto = 0x00,
    ciudad = 0x01,
    campo = 0x02
};

struct DatoDeViga {
    float x;
    float y;
    float angulo;
    TipoViga tipo;

    DatoDeViga(float, float, float, TipoViga);
};

class NetMessageInitialGameState : public NetMessage {
    public:
    float ancho_escenario;
    float alto_escenario;
    TipoEscenario tipo_escenario;
    std::vector<DatoDeViga> vigas;
    
    NetMessageInitialGameState();

    virtual void push_data_into(NetBuffer& container) override;
    virtual void pull_data_from(NetProtocolInterpreter& channel) override;
    virtual void execute(NetMessageBehaviour& interpreter) override;
};
#endif
