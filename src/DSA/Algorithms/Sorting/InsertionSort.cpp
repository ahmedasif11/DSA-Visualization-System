#include "InsertionSort.h"
#include "../../Array/Array.h"
#include <sstream>
#include <map>

namespace DSA {

std::vector<SortStep> InsertionSort::sort(const Array& array) {
    std::vector<SortStep> steps;

    if (array.size() <= 1) {
        if (array.size() == 1) {
            steps.push_back(createCompleteStep(array));
        }
        return steps;
    }

    Array workingArray = array;
    
    std::size_t n = workingArray.size();

    for (std::size_t i = 1; i < n; ++i) {
        int key = workingArray[i];
        std::size_t j = i;
        
        std::ostringstream highlightMsg;
        highlightMsg << "Selecting element at index " << i 
                     << " (value: " << key << ") to insert";
        std::vector<std::size_t> highlightIndices = {i};
        std::map<std::size_t, ElementRole> roles;
        roles[i] = ElementRole::Key;
        
        SortStep keyStep = createHighlightStep(workingArray, highlightIndices, roles, highlightMsg.str());
        keyStep.setAnnotation("key", std::to_string(key));
        steps.push_back(keyStep);
        
        while (j > 0 && workingArray[j - 1] > key) {
            std::ostringstream compareMsg;
            compareMsg << "Comparing element at index " << (j - 1) 
                       << " (value: " << workingArray[j - 1] 
                       << ") with key (value: " << key << ")";
            std::vector<std::size_t> compareIndices = {j - 1, j};
            
            SortStep compareStep = createCompareStep(workingArray, compareIndices, compareMsg.str());
            compareStep.setAnnotation("key", std::to_string(key));
            steps.push_back(compareStep);
            
            workingArray[j] = workingArray[j - 1];
            --j;
            
            std::ostringstream shiftMsg;
            shiftMsg << "Shifting element at index " << (j) 
                     << " to index " << (j + 1);
            std::vector<std::size_t> shiftIndices = {j, j + 1};
            
            SortStep shiftStep = createHighlightStep(workingArray, shiftIndices, shiftMsg.str());
            shiftStep.setAnnotation("key", std::to_string(key));
            steps.push_back(shiftStep);
        }
        
        if (j != i) {
            workingArray[j] = key;
            
            std::ostringstream insertMsg;
            insertMsg << "Inserting key at index " << j;
            std::vector<std::size_t> insertIndices = {j};
            steps.push_back(createHighlightStep(workingArray, insertIndices, insertMsg.str()));
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

std::string InsertionSort::getDescription() const {
    return "Insertion Sort builds a sorted array one element at a time by "
           "inserting each element into its correct position in the sorted portion. "
           "Similar to how you sort playing cards in your hand.";
}

}
