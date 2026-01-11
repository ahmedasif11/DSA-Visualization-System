

#pragma once

#include "SorterBase.h"

namespace DSA {


class BubbleSort : public SorterBase {
public:
    
    BubbleSort() = default;
    
    
    virtual ~BubbleSort() = default;
    
    
    std::vector<SortStep> sort(const Array& array) override;
    
    
    std::string getName() const override { return "Bubble Sort"; }
    
    
    std::string getDescription() const override;
    
    
    std::string getTimeComplexity() const override { return "O(n²)"; }
    
    
    std::string getSpaceComplexity() const override { return "O(1)"; }
};

} 
