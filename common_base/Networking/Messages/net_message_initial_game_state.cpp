#include "net_message_initial_game_state.h"

NetMessageInitialGameState::NetMessageInitialGameState()
    : NetMessage(NET_MESSAGE_TYPE_CHAT)
    {}


void NetMessageInitialGameState::push_data_into(NetBuffer& container) {
    NetMessage::push_data_into(container);
    container.push_float(ancho_escenario);
    container.push_float(alto_escenario);
    container.push_byte(static_cast<uint8_t>(tipo_escenario));
    container.push_short(vigas.size());
    for(auto it : vigas) {
        container.push_float(it.x);
        container.push_float(it.y);
        container.push_float(it.angulo);
        container.push_byte(static_cast<uint8_t>(it.tipo));
    }
}

void NetMessageInitialGameState::pull_data_from(NetProtocolInterpreter& channel) {
    ancho_escenario = channel.read_float();
    alto_escenario = channel.read_float();
    tipo_escenario = static_cast<TipoEscenario>(channel.read_byte());
    short size = channel.read_short();
    for(short i = 0; i < size; i++) {
        vigas.emplace_back(
            channel.read_float(),
            channel.read_float(),
            channel.read_float(),
            static_cast<TipoViga>(channel.read_byte())
        );
    }

    container.push_byte(static_cast<uint8_t>(tipo_escenario));
    container.push_short(vigas.size());
    for(auto it : vigas) {
        container.push_float(it.x);
        container.push_float(it.y);
        container.push_float(it.angulo);
        container.push_byte(static_cast<uint8_t>(it.tipo));
    }
    client_id = channel.read_uint();
    chat = channel.read_string();
}

void NetMessageInitialGameState::execute(NetMessageBehaviour& interpreter) {
    interpreter.run(this);
}
