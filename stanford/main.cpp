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

int main(int argc, const char *argv[]) {
    std::vector<EdgeWithWeight> edges;

    std::ifstream file("/Users/karacam/desktop/projects/stanford/stanford/input.txt");
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file." << std::endl;
        return 1;
    }

    std::string line;
    
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int index;
        iss >> index;
        index--;

        std::string edgeData;
        while (iss >> edgeData) {
            size_t commaPos = edgeData.find(',');
            if (commaPos != std::string::npos) {
                int w = std::stoi(edgeData.substr(0, commaPos)) - 1;
                int weight = std::stoi(edgeData.substr(commaPos + 1));
                
                EdgeWithWeight edge = {index, w, weight};

                edges.push_back(edge);
            }
        }
    }

    file.close();
    
    std::string result = get_shortest_path(edges);
    
    std::cout << result << "\n";

    return 0;
}
