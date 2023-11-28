#include "CFragments.h"

CFragments::CFragments(
    std::unique_ptr<FragmentsInfo> frag_info
) : m_fragments_info(std::move(frag_info)) {}

const std::unique_ptr<FragmentsInfo>& CFragments::info() const {
    return m_fragments_info;
}