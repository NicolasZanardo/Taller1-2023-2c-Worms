#ifndef __GAME_INFO_DTO_H__
#define __GAME_INFO_DTO_H__

#include <cstdint>
#include <string>

class GameInfoDTO {
public:
    std::string game_room;
    std::string scenario;
    uint8_t joined_players;
    uint8_t total_players;
};


#endif  // __GAME_INFO_DTO_H__
