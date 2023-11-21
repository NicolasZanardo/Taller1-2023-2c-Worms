#ifndef TP_WORMS_INSTANCESSYSTEM_H
#define TP_WORMS_INSTANCESSYSTEM_H

#include <unordered_map>
#include "../../model/worm/Worm.h"

class InstancesSystem {
public:
    void update(const std::unordered_map<size_t, std::shared_ptr<Worm>> &worms, std::shared_ptr<Worm> &current_worm);
};


#endif
