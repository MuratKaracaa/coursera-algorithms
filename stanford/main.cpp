//
//  main.cpp
//  stanford
//
//  Created by Murat Karaca on 10/27/24.
//


#include "knapsack/knapsack.h"
#include <fstream>
#include <iostream>

int main(int argc, const char *argv[]) {


    std::ifstream file("/Users/karacam/desktop/projects/stanford/stanford/input.txt");
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file." << std::endl;
        return 1;
    }
    
    int res = knapsack(file);
    
    std::cout << res << "\n";

    return 0;
}
