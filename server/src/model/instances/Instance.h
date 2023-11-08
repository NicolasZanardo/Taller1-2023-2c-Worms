#ifndef SERVER_ENTITY_H
#define SERVER_ENTITY_H

#include <cstddef>

class Instance {
public:
    size_t id;
    Instance(size_t id) : id(id) {}
};

#endif
