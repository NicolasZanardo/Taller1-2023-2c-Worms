#ifndef TP_WORMS_INSTANCESSYSTEM_H
#define TP_WORMS_INSTANCESSYSTEM_H

#include <unordered_map>
#include "../../model/worm/Worm.h"
#include "../../core/InstancesManager.h"

class InstancesSystem {
public:
    InstancesSystem() = default;
    void update(const std::unordered_map<size_t, std::shared_ptr<Worm>> &worms);
};


#endif
