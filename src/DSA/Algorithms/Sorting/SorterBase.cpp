#include "SorterBase.h"

namespace DSA {

SortStep SorterBase::createCompareStep(const Array& array,
                                       const std::vector<std::size_t>& indices,
                                       const std::string& message) const {
    return SortStep(StepType::Compare, indices, message, array);
}

SortStep SorterBase::createSwapStep(const Array& array,
                                    std::size_t i,
                                    std::size_t j,
                                    const std::string& message) const {
    Array swappedArray = array;
    swappedArray.swap(i, j);
    
    std::vector<std::size_t> indices = {i, j};
    return SortStep(StepType::Swap, indices, message, swappedArray);
}

SortStep SorterBase::createHighlightStep(const Array& array,
                                         const std::vector<std::size_t>& indices,
                                         const std::string& message) const {
    return SortStep(StepType::Highlight, indices, message, array);
}

SortStep SorterBase::createHighlightStep(const Array& array,
                                         const std::vector<std::size_t>& indices,
                                         const std::map<std::size_t, ElementRole>& roles,
                                         const std::string& message) const {
    return SortStep(StepType::Highlight, indices, roles, message, array);
}

SortStep SorterBase::createCompleteStep(const Array& array) const {
    return SortStep(StepType::Complete, {}, "Sorting completed", array);
}

}
