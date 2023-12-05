#ifndef TP_WORMS_COUNTDOWNPROJECTILE_H
#define TP_WORMS_COUNTDOWNPROJECTILE_H

#include "Projectile.h"

class CountdownProjectile : public Projectile {
    friend class ProjectileFactory;

    int countdown_timer;

    explicit CountdownProjectile(size_t id, const std::unique_ptr<ProjectileInfo> &info);

    void update(int it, int rate) override;

    void on_collision(b2Vec2 collision_point) override;

};


#endif //TP_WORMS_COUNTDOWNPROJECTILE_H
