#ifndef TP_WORMS_PROJECTILE_H
#define TP_WORMS_PROJECTILE_H

#include <memory>
#include "../core/Updatable.h"
#include "../core/Instance.h"
#include "ProjectileBody.h"
#include "../../../../../common_base/Game/WeaponTypeDto.h"
#include "../../../../../common_base/Game/ProjectileDto.h"
#include "ProjectileInfo.h"

class InstancesManager;

class Projectile: public Instance, Updatable {
    friend class InstancesManager;
    size_t shooter_id;
    WeaponTypeDto weapon_type;

    bool exploded;
    explicit Projectile(size_t id, const std::unique_ptr<ProjectileInfo> &info);
public:
    Damage& damage;
    std::unique_ptr<ProjectileBody> body;
    b2Body* B2Body();
    float ExplosionRadius();

    void update(int it) override;
    ProjectileDto to_dto() const;
    void explode();
    bool has_exploded();
    void on_collision();
};


#endif //TP_WORMS_PROJECTILE_H
