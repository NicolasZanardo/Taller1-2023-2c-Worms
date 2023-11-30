#ifndef __CLIENT_PARSER_H__
#define __CLIENT_PARSER_H__

#include <memory>
#include <string>

#include "networking.h"

class LobbyParser {
public:
    Parser() = default;
    ~Parser() = default;

    Parser(const Parser& other) = delete;
    Parser &operator=(const Parser& other) = delete;

    Parser(Parser&& other) = delete;
    Parser &operator=(Parser&& other) = delete;

    std::unique_ptr<NetMessage> parse(const std::string& str);
};

#endif  // __CLIENT_PARSER_HPP__
