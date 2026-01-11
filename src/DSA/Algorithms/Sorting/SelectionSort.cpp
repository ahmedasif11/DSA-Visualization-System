#include "SelectionSort.h"
#include "../../Array/Array.h"
#include <sstream>
#include <map>

namespace DSA {

std::vector<SortStep> SelectionSort::sort(const Array& array) {
    std::vector<SortStep> steps;

    if (array.size() <= 1) {
        if (array.size() == 1) {
            steps.push_back(createCompleteStep(array));
        }
        return steps;
    }

    Array workingArray = array;
    
    std::size_t n = workingArray.size();

    for (std::size_t i = 0; i < n - 1; ++i) {
        std::size_t minIndex = i;
        
        std::ostringstream startMsg;
        startMsg << "Starting pass " << (i + 1) << ", searching for minimum from index " << i;
        std::vector<std::size_t> startIndices = {i};
        std::map<std::size_t, ElementRole> startRoles;
        startRoles[i] = ElementRole::Minimum;
        SortStep startStep = createHighlightStep(workingArray, startIndices, startRoles, startMsg.str());
        startStep.setAnnotation("minimum", std::to_string(workingArray[minIndex]));
        steps.push_back(startStep);
        
        for (std::size_t j = i + 1; j < n; ++j) {
            std::ostringstream compareMsg;
            compareMsg << "Comparing element at index " << j 
                       << " (value: " << workingArray[j] 
                       << ") with minimum at index " << minIndex 
                       << " (value: " << workingArray[minIndex] << ")";
            std::vector<std::size_t> compareIndices = {j, minIndex};
            SortStep compareStep = createCompareStep(workingArray, compareIndices, compareMsg.str());
            std::map<std::size_t, ElementRole> compareRoles;
            compareRoles[minIndex] = ElementRole::Minimum;
            compareStep.roles = compareRoles;
            compareStep.setAnnotation("minimum", std::to_string(workingArray[minIndex]));
            steps.push_back(compareStep);
            
            if (workingArray[j] < workingArray[minIndex]) {
                minIndex = j;
                
                std::ostringstream newMinMsg;
                newMinMsg << "New minimum found at index " << minIndex 
                          << " (value: " << workingArray[minIndex] << ")";
                std::vector<std::size_t> minIndices = {minIndex};
                std::map<std::size_t, ElementRole> roles;
                roles[minIndex] = ElementRole::Minimum;
                
                SortStep minStep = createHighlightStep(workingArray, minIndices, roles, newMinMsg.str());
                minStep.setAnnotation("minimum", std::to_string(workingArray[minIndex]));
                steps.push_back(minStep);
            }
        }
        
        if (minIndex != i) {
            std::ostringstream swapMsg;
            swapMsg << "Swapping minimum at index " << minIndex 
                    << " (value: " << workingArray[minIndex] 
                    << ") with element at index " << i 
                    << " (value: " << workingArray[i] << ")";
            SortStep swapStep = createSwapStep(workingArray, i, minIndex, swapMsg.str());
            std::map<std::size_t, ElementRole> swapRoles;
            swapRoles[minIndex] = ElementRole::Minimum;
            swapStep.roles = swapRoles;
            swapStep.setAnnotation("minimum", std::to_string(workingArray[minIndex]));
            steps.push_back(swapStep);
            
            workingArray.swap(i, minIndex);
        } else {
            std::ostringstream noSwapMsg;
            noSwapMsg << "Element at index " << i 
                      << " is already in correct position";
            std::vector<std::size_t> noSwapIndices = {i};
            std::map<std::size_t, ElementRole> noSwapRoles;
            noSwapRoles[i] = ElementRole::Minimum;
            SortStep noSwapStep = createHighlightStep(workingArray, noSwapIndices, noSwapRoles, noSwapMsg.str());
            noSwapStep.setAnnotation("minimum", std::to_string(workingArray[i]));
            steps.push_back(noSwapStep);
        }
        
        std::ostringstream sortedMsg;
        sortedMsg << "Elements up to index " << i << " are now sorted";
        std::vector<std::size_t> sortedIndices;
        std::map<std::size_t, ElementRole> sortedRoles;
        for (std::size_t k = 0; k <= i; ++k) {
            sortedIndices.push_back(k);
            sortedRoles[k] = ElementRole::Sorted;
        }
        steps.push_back(createHighlightStep(workingArray, sortedIndices, sortedRoles, sortedMsg.str()));
    }

    steps.push_back(createCompleteStep(workingArray));
    
    return steps;
}

std::string SelectionSort::getDescription() const {
    return "Selection Sort repeatedly finds the minimum element from the "
           "unsorted portion and places it at the beginning. "
           "Similar to repeatedly selecting the smallest card from a deck.";
}

}
