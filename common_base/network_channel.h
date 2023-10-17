#ifndef COMMON_SOCKET_MEDIATOR_H_
#define COMMON_SOCKET_MEDIATOR_H_

#include <vector>
#include <string>
#include <cstdint>
#include "socket.h"

class NetworkChannel {
    private:
    // Eliminar accion de copiado
    NetworkChannel(const NetworkChannel &other) = delete;
    NetworkChannel operator=(const NetworkChannel &other) = delete;
    void move_action(NetworkChannel&);

    protected:
    unsigned int index;
    unsigned int read_index;
    std::vector<char> data;
    Socket &skt;

    public:
    explicit NetworkChannel(Socket &skt);

    // Crear accion de movimiento inteligente
    NetworkChannel(NetworkChannel&&);
    NetworkChannel& operator=(NetworkChannel&&);

    // Insertar valores en la cola de bytes del buffer para 
    void push_byte(const uint8_t value);
    void push_short(const uint16_t value);
    void push_uint(const uint32_t value);
    void push_string(const std::string &value);

    // Recuperar valores desde los bytes ya leido del buffer.
    uint8_t     get_byte();
    uint16_t    get_short();
    uint32_t    get_uint();
    std::string get_string(const uint16_t size);

    // Estas funciones estan para mantener privados los atributos del Buffer
    // Y para centralizar y no repetir el codigo
    // encargado de envio de informacion por el socket
    bool send();
    bool read(unsigned int msgSize);
    void clear();

    // Recuperar valores directamente desde el canal de coneccion.
    uint8_t     read_byte();
    uint16_t    read_short();
    uint32_t    read_uint();
    std::string read_string();
};

#endif
