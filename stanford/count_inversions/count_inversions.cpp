//
//  count_inversions.cpp
//  stanford
//
//  Created by Murat Karaca on 11/1/24.
//

#include "count_inversions.h"

InversionCount count_inversions(const InversionCount& obj){
    int arraySize = obj.vectorToCount.size();
    if(arraySize > 1){
        int mid = arraySize / 2;
        std::vector<int> firstHalf(obj.vectorToCount.begin(), obj.vectorToCount.begin() + mid);
        std::vector<int> secondHalf(obj.vectorToCount.begin() + mid, obj.vectorToCount.end());
        
        InversionCount firstObj{firstHalf, 0};
        InversionCount secondObj{secondHalf, 0};
        
        InversionCount sortedFirst = count_inversions(firstObj);
        InversionCount sortedSecond = count_inversions(secondObj);
        
        std::vector<int> result(arraySize);
        int i {0};
        int j {0};
        long inversionNumber = 0;
        
        for(int k {0}; k<arraySize;k++){
            if(i == sortedFirst.vectorToCount.size()) {
                result[k] = sortedSecond.vectorToCount[j];
                j++;
            }
            else if(j == sortedSecond.vectorToCount.size()) {
                result[k] = sortedFirst.vectorToCount[i];
                i++;
            }
            else if(sortedFirst.vectorToCount[i] < sortedSecond.vectorToCount[j]) {
                result[k] = sortedFirst.vectorToCount[i];
                i++;
            }
            else {
                result[k] = sortedSecond.vectorToCount[j];
                inversionNumber += sortedFirst.vectorToCount.size() - i;
                j++;
            }
        }
        
        return InversionCount{result, inversionNumber + sortedFirst.inversionCount + sortedSecond.inversionCount};
    } else {
        return obj;
    }
}

