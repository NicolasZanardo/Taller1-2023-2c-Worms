#include "WormIdIterator.h"
#include <iostream>
#include <algorithm>
using namespace std;

WormIdIterator::WormIdIterator(const list<int>& worms_ids) :
    m_worms_ids(worms_ids),
    current_worm_iterator(m_worms_ids.begin()) {}


int WormIdIterator::get_current_worm() const {
    return *current_worm_iterator;
}

int WormIdIterator::advance_to_next_worm_id() {
    if (m_worms_ids.empty()) {
        throw out_of_range("No remaining worms in the list");
    }
    ++current_worm_iterator;
    if (current_worm_iterator == m_worms_ids.end()) {
        current_worm_iterator = m_worms_ids.begin();
    }
    return *current_worm_iterator;
}

bool WormIdIterator::remove_worm_id(int worm_id) {
    auto it = find(m_worms_ids.begin(), m_worms_ids.end(), worm_id);
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

bool WormIdIterator::is_empty() const {
    return m_worms_ids.empty();
}
