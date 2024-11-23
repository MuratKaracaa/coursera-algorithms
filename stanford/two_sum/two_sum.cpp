//
//  two_sum.cpp
//  stanford
//
//  Created by Murat Karaca on 11/22/24.
//

#include "two_sum.h"
#include <sstream>
#include <set>
#include <unordered_set>
#include <iostream>

int two_sum(std::ifstream& file){
    std::set<long> sorted;
    std::unordered_set<long> unsorted;
    std::unordered_set<long> sum_set;
    
    std::string line;
    
    while(std::getline(file, line)){
        std::istringstream iss(line);
        long number;
        iss >> number;
        sorted.insert(number);
        unsorted.insert(number);
    }
    
    file.close();
    
    for(long number: unsorted){
        long low = -10000 - number;
        long high = 10000 - number;
        
        auto start = sorted.lower_bound(low);
        auto end = sorted.upper_bound(high);
        
        for(auto iterator = start; iterator != end;++iterator){
            long number_in_range = *iterator;
            if(number != number_in_range){
                sum_set.insert(number_in_range + number);
            }
        }
    }

    return sum_set.size();
}
