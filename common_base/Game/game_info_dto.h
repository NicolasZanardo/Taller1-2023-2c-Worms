#ifndef __GAME_INFO_DTO_H__
#define __GAME_INFO_DTO_H__

#include <cstdint>
#include <string>

class GameInfoDTO {
public:
    GameInfoDTO() = default;

    explicit GameInfoDTO(const std::string& name, const std::string& scenario, uint8_t total_players, uint8_t joined_players)
        : name(name), scenario(scenario)
        , total_players(total_players), joined_players(joined_players) {}
    
    ~GameInfoDTO() = default;

    GameInfoDTO(GameInfoDTO&& other)
        : name(std::move(other.name))
        , scenario (std::move(other.scenario))
        , total_players(other.total_players)
        , joined_players(other.joined_players) {}
    
    GameInfoDTO& operator=(GameInfoDTO&& other) {
        if (this == &other) {
            return *this;
        }

        this->name = std::move(other.name);
        this->scenario = std::move(other.scenario);
        this->joined_players = other.joined_players;
        this->total_players = other.total_players;

        return *this;
    }

    std::string name;
    std::string scenario;
    uint8_t total_players;
    uint8_t joined_players;
};

#endif  // __GAME_INFO_DTO_H__
