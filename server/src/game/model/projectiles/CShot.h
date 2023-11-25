#ifndef TP_WORMS_CSHOT_H
#define TP_WORMS_CSHOT_H

#include <vector>
#include "ProjectileInfo.h"

class CShot {
    float shot_angle;
    std::vector<std::unique_ptr<ProjectileInfo>> projectiles;
public:
    CShot(std::unique_ptr<ProjectileInfo> projectile_info, float aimed_angle);
    CShot(std::vector<std::unique_ptr<ProjectileInfo>> projectiles, float aimed_angle);

    const std::vector<std::unique_ptr<ProjectileInfo>>& Projectiles() const;
    float ShotAngle() const;
};


#endif //TP_WORMS_CSHOT_H
