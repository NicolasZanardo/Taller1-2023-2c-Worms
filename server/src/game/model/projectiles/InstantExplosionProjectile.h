#ifndef TP_WORMS_INSTANTEXPLOSIONPROJECTILE_H
#define TP_WORMS_INSTANTEXPLOSIONPROJECTILE_H

#include "Projectile.h"

class InstantExplosionProjectile : public Projectile {
    friend class ProjectileFactory;

    explicit InstantExplosionProjectile(size_t id, const std::unique_ptr<ProjectileInfo> &info);
    explicit InstantExplosionProjectile(size_t id, const std::unique_ptr<FragmentsInfo> &info);

    void on_collision(b2Vec2 collision_point) override;

};


#endif //TP_WORMS_INSTANTEXPLOSIONPROJECTILE_H
