#ifndef TP_WORMS_SHOT_H
#define TP_WORMS_SHOT_H

#include <vector>
#include "ProjectileInfo.h"

class Shot {
    float shot_angle;
    std::vector<std::shared_ptr<ProjectileInfo>> projectiles;
public:
    Shot(const std::shared_ptr<ProjectileInfo>&, float aimed_angle);
    Shot(const std::vector<std::shared_ptr<ProjectileInfo>>& projectiles, float aimed_angle);
    const std::vector<std::shared_ptr<ProjectileInfo>>& Projectiles() const;

    float ShotAngle() const;
};


#endif //TP_WORMS_SHOT_H
