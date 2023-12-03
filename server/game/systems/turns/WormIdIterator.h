/*#ifndef TP_WORMS_WORMIDITERATOR_H
#define TP_WORMS_WORMIDITERATOR_H

#include <list>

class WormIdIterator {
private:
    std::list<int> m_worms_ids;
    std::list<int>::iterator current_worm_iterator;
public:
    explicit WormIdIterator(const std::list<int>& worms_ids);

    int get_current_worm() const;
    int advance_to_next_worm_id();
    bool remove_worm_id(int worm_id);

    bool is_empty() const;
};

#endif
*/