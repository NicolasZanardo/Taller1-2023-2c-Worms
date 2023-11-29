#ifndef TP_WORMS_PROJECTILEFACTORY_H
#define TP_WORMS_PROJECTILEFACTORY_H

#include <memory>
#include "Projectile.h"
#include "ProjectileInfo.h"

class ProjectileFactory {
public:
    static std::shared_ptr<Projectile> create_projectile(size_t id, const std::unique_ptr<ProjectileInfo> &info);
    static std::shared_ptr<Projectile> create_fragment_projectile(size_t id, const std::unique_ptr<FragmentsInfo> &info);
};


#endif //TP_WORMS_PROJECTILEFACTORY_H
