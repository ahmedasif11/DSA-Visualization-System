#pragma once

#include "SortStep.h"
#include "../../Array/Array.h"
#include <string>
#include <vector>
#include <map>

namespace DSA {

class SorterBase {
public:
    virtual ~SorterBase() = default;
    virtual std::vector<SortStep> sort(const Array& array) = 0;
    virtual std::string getName() const = 0;
    virtual std::string getDescription() const = 0;
    virtual std::string getTimeComplexity() const = 0;
    virtual std::string getSpaceComplexity() const = 0;

protected:
    SortStep createCompareStep(const Array& array, 
                               const std::vector<std::size_t>& indices,
                               const std::string& message) const;
    
    SortStep createSwapStep(const Array& array,
                           std::size_t i,
                           std::size_t j,
                           const std::string& message) const;
    
    SortStep createHighlightStep(const Array& array,
                                const std::vector<std::size_t>& indices,
                                const std::string& message) const;
    
    SortStep createHighlightStep(const Array& array,
                                const std::vector<std::size_t>& indices,
                                const std::map<std::size_t, ElementRole>& roles,
                                const std::string& message) const;
    
    SortStep createCompleteStep(const Array& array) const;
};

}
