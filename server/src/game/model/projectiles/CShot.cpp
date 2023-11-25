#include "CShot.h"

CShot::CShot(std::unique_ptr<ProjectileInfo> projectile_info)
    :  projectiles() {
    projectiles.push_back(std::move(projectile_info));
}

CShot::CShot(std::vector<std::unique_ptr<ProjectileInfo>> projectiles) :
    projectiles(std::move(projectiles)) {}

const std::vector<std::unique_ptr<ProjectileInfo>>& CShot::Projectiles() const {
    return projectiles;
}