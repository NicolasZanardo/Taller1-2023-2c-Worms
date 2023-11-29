#ifndef TP_WORMS_WORMFOOTSENSOR_H
#define TP_WORMS_WORMFOOTSENSOR_H

#include "Collidable.h"

class Worm;

class WormFootSensor: public Collidable {
public:
    Worm* worm;
    explicit WormFootSensor(Worm* worm);

    void sense_ground_contact() const;
    void sense_ground_contact_ended() const;
};


#endif //TP_WORMS_WORMFOOTSENSOR_H
