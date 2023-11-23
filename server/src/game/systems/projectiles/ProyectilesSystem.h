#ifndef TP_WORMS_PROYECTILESYSTEM_H
#define TP_WORMS_PROYECTILESYSTEM_H

#include <vector>
#include "../../model/projectiles/ProjectileInfo.h"

class ProyectilesSystem {
public:
    ProyectilesSystem() = default;
    void update(std::vector<ProjectileInfo>& projectiles);

};


#endif //TP_WORMS_PROYECTILESYSTEM_H
