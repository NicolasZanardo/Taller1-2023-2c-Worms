#include "id_generator.h"

IDGenerator::IDGenerator()
    : next_id(0) {}  // 0 es un ID reservado.

uint32_t IDGenerator::getNextID() {
    if (this->released_ids.empty()) {
        this->next_id++;

        return this->next_id;
    }

    uint32_t ret_id = this->released_ids.front();
    this->released_ids.pop();

    return ret_id;
}

void IDGenerator::releaseID(uint32_t id) {
    this->released_ids.push(id);
}
