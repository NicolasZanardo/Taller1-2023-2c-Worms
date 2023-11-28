#ifndef TP_WORMS_CFRAGMENTS_H
#define TP_WORMS_CFRAGMENTS_H

#include <memory>
#include <vector>
#include "FragmentsInfo.h"

class CFragments {
    std::unique_ptr<FragmentsInfo> m_fragments_info;
public:
    explicit CFragments(std::unique_ptr<FragmentsInfo> fragments_info);

    const std::unique_ptr<FragmentsInfo>& info() const;

};


#endif //TP_WORMS_CFRAGMENTS_H
