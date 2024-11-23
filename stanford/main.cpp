//
//  main.cpp
//  stanford
//
//  Created by Murat Karaca on 10/27/24.
//

#include <fstream>
#include <sstream>
#include <string>
#include <ostream>
#include <iostream>
#include <vector>
#include "two_sum/two_sum.h"
#include <set>


int main(int argc, const char *argv[]) {


    std::ifstream file("/Users/karacam/desktop/projects/stanford/stanford/input.txt");
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file." << std::endl;
        return 1;
    }
    
    std::set<int> myset = {1,2,3,4,5,6,7,8};
    
    int low = 12, high = 10;
    auto start = myset.lower_bound(low);
    auto end = myset.upper_bound(high);

    for (auto it = start; it != end; ++it) {
        std::cout << *it << " ";
    }


    int size = two_sum(file);
    
    std::cout << size << "\n";

    return 0;
}
