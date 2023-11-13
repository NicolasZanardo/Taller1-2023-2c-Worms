#include "WormIdIterator.h"
#include <iostream>

WormIdIterator::WormIdIterator(const std::list<size_t>& worms_ids) :
    m_worms_ids(worms_ids),
    current_worm_iterator(m_worms_ids.begin()) {}


size_t WormIdIterator::getCurrentWorm() const {
    return *current_worm_iterator;
}

size_t WormIdIterator::advance_to_next_worm_id() {
    if (m_worms_ids.empty()) {
        throw std::out_of_range("No remaining worms in the list");
    }
    std::cout << "Current worm id was: " << *current_worm_iterator << std::endl;
    ++current_worm_iterator;
    if (current_worm_iterator == m_worms_ids.end()) {
        current_worm_iterator = m_worms_ids.begin();
    }
    std::cout << "Current worm id is: " << *current_worm_iterator << std::endl;
    return *current_worm_iterator;
}

bool WormIdIterator::remove_worm_id(size_t worm_id) {
    auto it = std::find(m_worms_ids.begin(), m_worms_ids.end(), worm_id);
    if (it != m_worms_ids.end()) {
        m_worms_ids.erase(it);

        // If the removed worm was the current worm, advance to the next worm
        if (current_worm_iterator != m_worms_ids.end() && *current_worm_iterator == worm_id) {
            advance_to_next_worm_id();
        }

        return true;  // Worm found and removed
    }

    return false;  // Worm not found
}