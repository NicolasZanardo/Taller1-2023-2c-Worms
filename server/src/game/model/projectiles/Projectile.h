#ifndef TP_WORMS_PROJECTILE_H
#define TP_WORMS_PROJECTILE_H

#include <memory>
#include "../core/Updatable.h"
#include "../core/Instance.h"
#include "ProjectileMovement.h"
#include "../../../../../common_base/Game/WeaponTypeDto.h"
#include "../../../../../common_base/Game/ProjectileDto.h"

class InstancesManager;

class Projectile: public Instance, Updatable {
    friend class InstancesManager;
    WeaponTypeDto weapon_type;
    explicit Projectile(size_t id, WeaponTypeDto weapon_type);
public:

    std::unique_ptr<ProjectileMovement> movement;

    void update() override;
    ProjectileDto to_dto() const;
};


#endif //TP_WORMS_PROJECTILE_H
