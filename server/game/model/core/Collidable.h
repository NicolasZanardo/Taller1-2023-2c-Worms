#ifndef TP_WORMS_COLLIDABLE_H
#define TP_WORMS_COLLIDABLE_H

#include <string>

class Collidable {
public:
    const std::string& tag;

    explicit Collidable(const std::string& tag)
        : tag(tag) {}


    virtual ~Collidable() = default;
};


#endif
