#include "CShot.h"

CShot::CShot(std::unique_ptr<ProjectileInfo> projectile_info, float aimed_angle)
    : shot_angle(aimed_angle), projectiles() {
    projectiles.push_back(std::move(projectile_info));
}

CShot::CShot(std::vector<std::unique_ptr<ProjectileInfo>> projectiles, float aimed_angle)
    : shot_angle(aimed_angle), projectiles(std::move(projectiles)) {}

const std::vector<std::unique_ptr<ProjectileInfo>>& CShot::Projectiles() const {
    return projectiles;
}

float CShot::ShotAngle() const {
    return shot_angle;
}