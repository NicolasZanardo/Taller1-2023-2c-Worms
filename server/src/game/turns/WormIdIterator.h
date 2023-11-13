#ifndef TP_WORMS_WORMIDLIST_H
#define TP_WORMS_WORMIDLIST_H

#include <list>

class WormIdList {
private:
    std::list<size_t> m_worms_ids;
    std::list<size_t>::iterator current_worm_iterator;
public:
    WormIdList(const std::list<size_t>& worms_ids);

    size_t getCurrentWorm() const;
    void advanceToNextWorm();
};


#endif
