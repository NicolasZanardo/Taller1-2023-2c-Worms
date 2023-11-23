//
// Created by Juan Martin Duzac on 22/11/2023.
//

#ifndef TP_WORMS_COMMAND_H
#define TP_WORMS_COMMAND_H


class Command {
public:
    /* Constructor */
    Command() {}

    /* Deshabilitamos el constructor por copia. */
    Command(const Command&) = delete;

    /* Deshabilitamos el operador= para copia.*/
    Command& operator=(const Command&) = delete;

    /* Deshabilitamos el constructor por movimiento. */
    Command(Command&& other) = delete;

    /* Deshabilitamos el operador= para movimiento. */
    Command& operator=(Command&& other) = delete;

    //-------------------------------------------------------------------------

    /* Envío polimórfico del comando. Devuelve si se pudo enviar o no. */
    virtual bool send(const SocketWrapper& socket) = 0;

    //-------------------------------------------------------------------------

    /* Destructor */
    virtual ~Command() {}
};


#endif //TP_WORMS_COMMAND_H
