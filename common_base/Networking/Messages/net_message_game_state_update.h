#ifndef COMMON_NET_MESSAGE_GAME_SATE_UPDATE_H_
#define COMMON_NET_MESSAGE_GAME_SATE_UPDATE_H_

#include <vector>
#include "net_message_dependencies.h"

enum class EstadoWorm : uint8_t {
    idle    = 0x00,
    walking = 0x01,
    jumping = 0x02,
    shooting= 0x03,
    dead    = 0x04,
    falling = 0x05,
    damaged = 0x06
};

// TODO: servidor o cliente?
enum class Facing : uint8_t {
    left  = 0x00,
    right = 0x01
};

struct DatoDeWorm {
    int client_id;
    int entity_id;
    float x;
    float y;
    int vida;
    EstadoWorm estado;

    DatoDeWorm(
        int client_id,
        int entity_id,
        float x,
        float y,
        int vida,
        EstadoWorm estado
    );
};

enum class TipoProyectil : uint8_t {
    ninguno = 0x00,
    bazooka = 0x01
};

struct DatoProyectil {
    int entity_id;
    float x;
    float y;
    float angulo;
    TipoProyectil tipo;

    DatoProyectil(
        int entity_id,
        float x,
        float y,
        float angulo,
        TipoProyectil tipo
    );
};

enum class TipoEvento : uint8_t {
    cajita = 0x00,
    explosion_1 = 0x01,
};

struct DatoEvento {
    int entity_id;
    float x;
    float y;
    TipoEvento tipo;

    DatoEvento(
        int entity_id,
        float x,
        float y,
        TipoEvento tipo
    );
};

class NetMessageGameStateUpdate : public NetMessage {
    public:
    int id_entidad_jugando;
    float velocidad_viento; // positivo o negativo
    float tiempo_restante_juego;
    float tiempo_restante_turno;
    std::vector<DatoDeWorm> worms;
    std::vector<DatoProyectil> proyectiles;
    std::vector<DatoEvento> eventos;
    
    NetMessageGameStateUpdate();
    NetMessageGameStateUpdate(const int client_id, const std::string chat);

    virtual void push_data_into(NetBuffer& container) override;
    virtual void pull_data_from(NetProtocolInterpreter& channel) override;
    virtual void execute(NetMessageBehaviour& interpreter) override;
};
#endif
