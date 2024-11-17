//
//  quick_sort.h
//  stanford
//
//  Created by Murat Karaca on 11/3/24.
//

#include <vector>

enum ComparisonType {
    FIRST,
    LAST,
    MEDIAN
};

void quick_sort(std::vector<int>& array,int left,int right ,long long& comparisonCount,ComparisonType comparisonType);
