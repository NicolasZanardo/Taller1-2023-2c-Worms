#ifndef TP_WORMS_CSHOT_H
#define TP_WORMS_CSHOT_H

#include <vector>
#include "ProjectileInfo.h"

class CShot {
    std::vector<std::unique_ptr<ProjectileInfo>> projectiles;
public:
    CShot(std::unique_ptr<ProjectileInfo> projectile_info);
    CShot(std::vector<std::unique_ptr<ProjectileInfo>> projectiles);

    const std::vector<std::unique_ptr<ProjectileInfo>>& Projectiles() const;
    float ShotAngle() const;
    char FacingSign() const;
};


#endif //TP_WORMS_CSHOT_H
