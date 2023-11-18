#ifndef __CLIENT_CONFIG_H__
#define __CLIENT_CONFIG_H__

#include <string>

class ClientConfig {
public:
    ClientConfig() = default;
    ~ClientConfig() = default;

    const std::string& getRoomName() const;
    uint32_t getClientId() const;

    void setRoomName(const std::string& room_name);
    void setClientID();

private:
    std::string room_name;
    uint32_t client_id;
    // bool ready_to_play;
    // bool sounds_effects;
    // bool music;
};

#endif  // __CLIENT_CONFIG_H__
