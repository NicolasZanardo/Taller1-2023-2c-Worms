#include "Instance.h"

Instance::Instance(int id) : id(id), is_active(true) {}

int Instance::Id() const {
    return id;
}

void Instance::Destroy() {
    is_active = false;
}

bool Instance::IsActive() {
    return is_active;
}



