#ifndef TP_WORMS_PROJECTILE_H
#define TP_WORMS_PROJECTILE_H

#include <memory>
#include <string>
#include "../core/Updatable.h"
#include "../core/Instance.h"
#include "ProjectileBody.h"
#include "../../../../../common_base/Game/WeaponTypeDto.h"
#include "../../../../../common_base/Game/ProjectileDto.h"
#include "ProjectileInfo.h"
#include "../core/Collidable.h"
#include "CExplosion.h"


class Projectile : public Collidable, public Instance, Updatable {
protected:
    WeaponTypeDto weapon_type;
    bool exploded;
    bool is_on_water;
    int on_water_time_life;
    bool wind_affected;
    std::unique_ptr<CExplosion> c_explosion;
public:
    explicit Projectile(size_t id, const std::unique_ptr<ProjectileInfo> &info);

    float max_damage;
    float explosion_radius;
    std::unique_ptr<ProjectileBody> body;

    b2Body *B2Body() const;

    void update(int it, int rate) override;

    ProjectileDto to_dto() const;

    void explode();

    bool has_exploded() const;
    bool is_wind_affected() const;

    virtual void on_collision() = 0;

    void sink();

    std::unique_ptr<CExplosion> explosion_component();

    ~Projectile() = default;
};


#endif //TP_WORMS_PROJECTILE_H
