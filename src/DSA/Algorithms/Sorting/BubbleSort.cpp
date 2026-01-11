/**
 * @file BubbleSort.cpp
 * @brief Implementation of Bubble Sort algorithm
 */

#include "BubbleSort.h"
#include "../../Array/Array.h"
#include <sstream>
#include <iomanip>

namespace DSA {

std::vector<SortStep> BubbleSort::sort(const Array& array) {
    std::vector<SortStep> steps;
    
    // Handle empty or single-element arrays
    if (array.size() <= 1) {
        if (array.size() == 1) {
            steps.push_back(createCompleteStep(array));
        }
        return steps;
    }
    
    // Create a working copy of the array
    Array workingArray = array;
    
    std::size_t n = workingArray.size();
    bool swapped;
    
    // Outer loop: number of passes
    for (std::size_t pass = 0; pass < n - 1; ++pass) {
        swapped = false;
        
        // Inner loop: compare adjacent elements
        for (std::size_t i = 0; i < n - 1 - pass; ++i) {
            std::size_t j = i + 1;
            
            // Create comparison step
            std::ostringstream msg;
            msg << "Comparing elements at indices " << i << " and " << j 
                << " (values: " << workingArray[i] << " and " << workingArray[j] << ")";
            
            std::vector<std::size_t> compareIndices = {i, j};
            steps.push_back(createCompareStep(workingArray, compareIndices, msg.str()));
            
            // Compare and swap if needed
            if (workingArray[i] > workingArray[j]) {
                // Create swap step
                std::ostringstream swapMsg;
                swapMsg << "Swapping elements at indices " << i << " and " << j 
                        << " (" << workingArray[i] << " > " << workingArray[j] << ")";
                
                steps.push_back(createSwapStep(workingArray, i, j, swapMsg.str()));
                
                // Perform the swap on working array
                workingArray.swap(i, j);
                swapped = true;
            }
        }
        
        // If no swaps occurred in this pass, array is sorted
        if (!swapped) {
            break;
        }
        
        // Highlight the last element of this pass (largest element bubbles to end)
        std::size_t lastIndex = n - 1 - pass;
        std::ostringstream highlightMsg;
        highlightMsg << "Pass " << (pass + 1) << " complete. Element at index " 
                     << lastIndex << " is in its final position.";
        
        std::vector<std::size_t> highlightIndices = {lastIndex};
        steps.push_back(createHighlightStep(workingArray, highlightIndices, highlightMsg.str()));
    }
    
    // Add completion step
    steps.push_back(createCompleteStep(workingArray));
    
    return steps;
}

std::string BubbleSort::getDescription() const {
    return "Bubble Sort repeatedly compares adjacent elements and swaps them "
           "if they are in the wrong order. Larger elements 'bubble up' to the "
           "end of the array with each pass.";
}

} // namespace DSA
