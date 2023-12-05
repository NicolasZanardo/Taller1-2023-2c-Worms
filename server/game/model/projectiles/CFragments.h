#ifndef TP_WORMS_CFRAGMENTS_H
#define TP_WORMS_CFRAGMENTS_H

#include <memory>
#include <vector>
#include "FragmentsInfo.h"

struct CFragments {

    std::unique_ptr<FragmentsInfo> info;

    explicit CFragments(
        std::unique_ptr<FragmentsInfo> frag_info
    ) : info(std::move(frag_info)) {}

};

#endif //TP_WORMS_CFRAGMENTS_H
