//
//  maintain_median.cpp
//  stanford
//
//  Created by Murat Karaca on 11/20/24.
//

#include <fstream>
#include <sstream>
#include "maintain_median.h"

int maintain_median(std::ifstream& file){
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
    std::priority_queue<int, std::vector<int>> maxHeap;
    int currentMedian = INT_MAX;
    //std::vector<int> mods;
    
    std::string line;
    
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int number;
        iss >> number;
        
        if(number <= currentMedian){
            maxHeap.push(number);
            if(maxHeap.size() - minHeap.size() == 2){
                minHeap.push(maxHeap.top());
                maxHeap.pop();
            }
        } else {
            minHeap.push(number);
            if(minHeap.size() - maxHeap.size() == 2){
                maxHeap.push(minHeap.top());
                minHeap.pop();
            }
        }
        
        if(maxHeap.size() > minHeap.size() || maxHeap.size() == minHeap.size()){
            currentMedian = maxHeap.top();
        } else {
            currentMedian = minHeap.top();
        }
        //mods.push_back(currentMedian);
    }

    file.close();

    //int sum = std::reduce(mods.begin(), mods.end());
    //return sum;
    
    return currentMedian;
}
