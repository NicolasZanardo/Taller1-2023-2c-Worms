#ifndef TP_WORMS_CONFIG_H
#define TP_WORMS_CONFIG_H

#include <unordered_map>
#include <cstdint>
#include <yaml-cpp/yaml.h>
#include <vector>
#include <string>

template <class T>
class Config {
private:
    std::unordered_map<int , T> config;
    void parse_file();

public:
    /* Constructor */
    Config() {
        parse_file();
    }

    Config(const Config&) = delete;
    Config& operator=(const Config&) = delete;
    Config(Config&& other) = delete;
    Config& operator=(Config&& other) = delete;

    // Define iterator type
    using iterator = typename std::unordered_map<int, T>::iterator;

    // Define const iterator type
    using const_iterator = typename std::unordered_map<int, T>::const_iterator;

    // Define begin and end functions
    iterator begin() { return config.begin(); }
    iterator end() { return config.end(); }

    const_iterator begin() const { return config.begin(); }
    const_iterator end() const { return config.end(); }

    // Get the first element
    T& front() {
        if (config.empty()) {
            throw std::out_of_range("Config is empty");
        }
        return config.begin()->second;
    }

    // Get the const first element
    const T& front() const {
        if (config.empty()) {
            throw std::out_of_range("Config is empty");
        }
        return config.begin()->second;
    }

};

#endif //TP_WORMS_CONFIG_H
