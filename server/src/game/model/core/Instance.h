#ifndef SERVER_ENTITY_H
#define SERVER_ENTITY_H

#include <cstddef>

class Instance {
protected:
    size_t id;
    bool is_active;
public:
    explicit Instance(size_t id);
    size_t Id() const;
    void Destroy();
    bool IsActive();

};

#endif
