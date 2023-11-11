#include "net_message.h"
#include <iostream>

NetMessage::NetMessage(uint8_t type) : msg_type(type) {}
NetMessage::~NetMessage() {}

void NetMessage::push_data_into(NetBuffer& container) {
    container.push_byte(msg_type);
}

