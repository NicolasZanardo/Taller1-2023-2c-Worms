#include "Instance.h"

Instance::Instance(size_t id) : id(id), is_active(true) {}

size_t Instance::Id() const {
    return id;
}

void Instance::Destroy() {
    is_active = false;
}

bool Instance::IsActive() {
    return is_active;
}



