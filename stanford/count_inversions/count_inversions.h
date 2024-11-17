//
//  count_inversions.h
//  stanford
//
//  Created by Murat Karaca on 11/1/24.
//

#include <vector>

struct InversionCount {
    std::vector<int> vectorToCount;
    long inversionCount;
    
    InversionCount(const std::vector<int>& vectorToCount, long inversionCount) : vectorToCount(vectorToCount), inversionCount(inversionCount){}
};

InversionCount count_inversions(const InversionCount& obj);
