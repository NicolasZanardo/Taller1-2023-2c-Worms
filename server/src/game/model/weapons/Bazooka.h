#ifndef TP_WORMS_BAZOOKA_H
#define TP_WORMS_BAZOOKA_H


#include "Weapon.h"

class Bazooka: public Weapon {
public:
    explicit Bazooka(int ammo_left, Damage damage);

    void start_shooting(std::shared_ptr<Worm> shooter) override;
    void end_shooting(std::shared_ptr<Worm> shooter) override;
};


#endif //TP_WORMS_BAZOOKA_H
