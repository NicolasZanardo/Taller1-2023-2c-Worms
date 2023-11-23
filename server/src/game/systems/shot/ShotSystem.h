#ifndef TP_WORMS_SHOTSYSTEM_H
#define TP_WORMS_SHOTSYSTEM_H

#include <memory>
#include "../../core/InstancesManager.h"
#include "../../model/worm/Worm.h"

class ShotSystem {
    InstancesManager &instances_manager;
public:
    explicit ShotSystem(InstancesManager &instances_manager);

    void update(const std::shared_ptr<Worm>& current_worm);
};


#endif
