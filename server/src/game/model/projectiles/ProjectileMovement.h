#ifndef TP_WORMS_PROJECTILEMOVEMENT_H
#define TP_WORMS_PROJECTILEMOVEMENT_H

#include <box2d/box2d.h>

class ProjectileMovement {
public:
    ProjectileMovement(b2Body* body);
    b2Body* body;

    float X() const;
    float Y() const;
};


#endif //TP_WORMS_PROJECTILEMOVEMENT_H
