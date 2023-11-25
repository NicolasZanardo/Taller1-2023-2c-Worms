#ifndef SERVER_ENTITY_H
#define SERVER_ENTITY_H

#include <cstddef>

class Instance {
public:
    size_t id;
    bool is_active;
    explicit Instance(size_t id) : id(id), is_active(true) {}

};

#endif
