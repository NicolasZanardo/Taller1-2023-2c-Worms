#ifndef TP_WORMS_WORMIDITERATOR_H
#define TP_WORMS_WORMIDITERATOR_H

#include <list>

class WormIdIterator {
private:
    std::list<std::size_t> m_worms_ids;
    std::list<std::size_t>::iterator current_worm_iterator;
public:
    explicit WormIdIterator(const std::list<std::size_t>& worms_ids);

    std::size_t get_current_worm() const;
    std::size_t advance_to_next_worm_id();
    bool remove_worm_id(std::size_t worm_id);

    bool is_empty() const;
};

#endif
