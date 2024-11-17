//
//  merge_sort.cpp
//  stanford
//
//  Created by Murat Karaca on 10/29/24.
//

#include <vector>
#include <limits>

#include "merge_sort.h"

std::vector<int> merge_sort(const std::vector<int>& array){
    int arraySize {(int)array.size()};
    if(arraySize > 1){
        std::vector<int> firstHalf{array.begin(), array.begin() + arraySize / 2};
        std::vector<int> secondHalf{array.begin() + arraySize / 2, array.begin() + arraySize};
        
        std::vector<int> sortedFirst {merge_sort(firstHalf)};
        std::vector<int> sortedSecond {merge_sort(secondHalf)};
        
        std::vector<int> result(arraySize,0);
        
        int i {0};
        int j {0};
        
        for(int k {0};k<arraySize;k++){
            int normalizedFirst {i < sortedFirst.size() ? sortedFirst[i] : std::numeric_limits<int>::max()};
            int normalizedSecond {j < sortedSecond.size() ? sortedSecond[j] : std::numeric_limits<int>::max()};
            if(normalizedFirst < normalizedSecond){
                result[k] = sortedFirst[i];
                i++;
            } else {
                result[k] = sortedSecond[j];
                j++;
            }
        }
        
        return result;
        
    } else {
        return array;
    }
}
