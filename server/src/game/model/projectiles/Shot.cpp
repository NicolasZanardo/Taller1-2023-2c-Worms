#include "Shot.h"

// Constructor for a single Projectile
Shot::Shot(const std::shared_ptr<ProjectileInfo> &projectile_info, float aimed_angle) : shot_angle(aimed_angle),
                                                                                        projectiles(
                                                                                            {projectile_info}) {}

// Constructor for a vector of Projectiles
Shot::Shot(const std::vector<std::shared_ptr<ProjectileInfo>> &projectiles, float aimed_angle) : shot_angle(
    aimed_angle), projectiles(
    projectiles) {}

const std::vector<std::shared_ptr<ProjectileInfo>> &Shot::Projectiles() const {
    return projectiles;
}

float Shot::ShotAngle() const {
    return shot_angle;
}
