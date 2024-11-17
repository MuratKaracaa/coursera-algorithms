#include "quick_sort.h"
#include <vector>


void quick_sort(std::vector<int>& array, int left, int right, long long& comparisonCount, ComparisonType comparisonType) {
    if (right >= left) {
        int pivotIndex = left;
        if (comparisonType == LAST) {
            pivotIndex = right;
        } else if (comparisonType == MEDIAN) {
            int first = array[left];
            int last = array[right];
            int middleIndex = (right + left) / 2;
            int middle = array[middleIndex];
            int median = first + last + middle - std::max(first, std::max(middle, last)) - std::min(first, std::min(middle, last));
            pivotIndex = (median == first) ? left : (median == last) ? right : middleIndex;
        }
        
        comparisonCount += right - left;

        if (pivotIndex != left) {
            std::swap(array[left], array[pivotIndex]);
        }

        int pivotValue = array[left];
        int i = left + 1;

        for (int j = i; j <= right; j++) {
            if (array[j] < pivotValue) {
                std::swap(array[j], array[i]);
                i++;
            }
        }

        std::swap(array[left], array[i - 1]);

        quick_sort(array, left, i - 2, comparisonCount, comparisonType);
        quick_sort(array, i, right, comparisonCount, comparisonType);
    }
}



