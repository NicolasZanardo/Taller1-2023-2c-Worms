#ifndef TP_WORMS_ROTATIONSTRATEGY_H
#define TP_WORMS_ROTATIONSTRATEGY_H

#include "box2d/box2d.h"

enum class RotationType {
    NONE , VELOCITY_ALIGNED, INITIAL_ANGULAR_VELOCITY
};

class RotationStrategy {
public:
    virtual ~RotationStrategy() = default;
    virtual void update_rotation(b2Body* body) const = 0;
};

class VelocityAlignedRotation : public RotationStrategy {
public:
    void update_rotation(b2Body* body) const override;
};

#endif
