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
#include "shortest_path/shortest_path.h"
#include <vector>
#include "maintain_median/maintain_median.h"

int main(int argc, const char *argv[]) {


    std::ifstream file("/Users/karacam/desktop/projects/stanford/stanford/input.txt");
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file." << std::endl;
        return 1;
    }

    int median = maintain_median(file);
    
    std::cout << median << "\n";

    return 0;
}
