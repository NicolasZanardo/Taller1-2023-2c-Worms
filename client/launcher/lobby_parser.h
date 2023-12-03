#ifndef __CLIENT_PARSER_H__
#define __CLIENT_PARSER_H__

#include <memory>
#include <string>

#include "networking.h"

class LobbyParser {
public:
    LobbyParser() = default;
    ~LobbyParser() = default;

    LobbyParser(const LobbyParser& other) = delete;
    LobbyParser &operator=(const LobbyParser& other) = delete;

    LobbyParser(LobbyParser&& other) = delete;
    LobbyParser &operator=(LobbyParser&& other) = delete;

    std::unique_ptr<NetMessage> parse(const std::string& str);
};

#endif  // __CLIENT_PARSER_HPP__
