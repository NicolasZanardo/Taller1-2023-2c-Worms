#ifndef SERVER_ENTITY_H
#define SERVER_ENTITY_H

#include <cstddef>

class Entity {
public:
    size_t id;
    Entity(size_t id) : id(id) {}
};

#endif
