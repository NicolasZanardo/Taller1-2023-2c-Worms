#include "WormIdList.h"

WormIdList::WormIdList(const std::list<size_t>& worms_ids) :
    m_worms_ids(worms_ids),
    current_worm_iterator(m_worms_ids.begin()) {}


size_t WormIdList::getCurrentWorm() const {
    return *current_worm_iterator;
}

void WormIdList::advanceToNextWorm() {
    ++current_worm_iterator;
    if (current_worm_iterator == m_worms_ids.end()) {
        current_worm_iterator = m_worms_ids.begin();
    }
}