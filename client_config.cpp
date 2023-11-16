#include "client_config.h"

const std::string& ClientConfig::getRoomName() const {
    return this->room_name;
}

uint32_t ClientConfig::getClientId() const {
    return this->client_id;
}

void ClientConfig::setRoomName(const std::string& room_name) {
    this->room_name = room_name;
}

void ClientConfig::setClientID(uint32_t client_id) {
    this->client_id = client_id;
}
