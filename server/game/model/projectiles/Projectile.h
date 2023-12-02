#ifndef TP_WORMS_PROJECTILE_H
#define TP_WORMS_PROJECTILE_H

#include <memory>
#include <string>
#include "Updatable.h"
#include "Instance.h"
#include "ProjectileBody.h"
#include "WeaponTypeDto.h"
#include "ProjectileDto.h"
#include "ProjectileInfo.h"
#include "Collidable.h"
#include "CExplosion.h"
#include "CFragments.h"
#include "ProjectileTypeDto.h"


class Projectile : public Collidable, public Instance, Updatable {
    constexpr static const float WATER_LIFE_TIME = 1500;
protected:
    ProjectileTypeDto type;
    bool exploded;
    bool is_on_water;
    int on_water_time_life;
    bool wind_affected;
    float max_damage;
    float explosion_radius;
    std::unique_ptr<CExplosion> c_explosion;
    std::unique_ptr<CFragments> c_fragments;
public:
    explicit Projectile(size_t id, const std::unique_ptr<ProjectileInfo> &info);

    explicit Projectile(size_t id, const std::unique_ptr<FragmentsInfo> &info);

    std::unique_ptr<ProjectileBody> body;

    ProjectileTypeDto get_type();

    float X() const;

    float Y() const;

    void update(int it, int rate) override;

    ProjectileDto to_dto() const;

    void receive(Force &force) const;

    void explode(float x, float y);

    bool has_exploded() const;

    virtual void on_collision(b2Vec2 explosion) = 0;

    void sink();

    std::unique_ptr<CExplosion> explosion_component();

    std::unique_ptr<CFragments> fragments_component();

    ~Projectile() = default;
};


#endif //TP_WORMS_PROJECTILE_H
