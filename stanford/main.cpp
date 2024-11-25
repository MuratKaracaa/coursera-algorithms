//
//  main.cpp
//  stanford
//
//  Created by Murat Karaca on 10/27/24.
//


#include "clustering/clustering.h"
#include <fstream>
#include <iostream>

int main(int argc, const char *argv[]) {


    std::ifstream file("/Users/karacam/desktop/projects/stanford/stanford/input.txt");
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file." << std::endl;
        return 1;
    }
    
    int sum = clustering_with_hamming_distance(file);
    
    std::cout << "mst:" << sum << "\n";

    return 0;
}
