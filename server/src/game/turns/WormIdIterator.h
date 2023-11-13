#ifndef TP_WORMS_WORMIDITERATOR_H
#define TP_WORMS_WORMIDITERATOR_H

#include <list>

class WormIdIterator {
private:
    std::list<size_t> m_worms_ids;
    std::list<size_t>::iterator current_worm_iterator;
public:
    explicit WormIdIterator(const std::list<size_t>& worms_ids);

    size_t getCurrentWorm() const;
    size_t advance_to_next_worm_id();
    bool remove_worm_id(size_t worm_id);
};

#endif
