#ifndef SERVER_ENTITY_H
#define SERVER_ENTITY_H

#include <cstddef>

class Instance {
protected:
    int id;
    bool is_active;
public:
    explicit Instance(int id);
    int Id() const;
    void Destroy();
    bool IsActive();
    bool is(int id) const;

};

#endif
