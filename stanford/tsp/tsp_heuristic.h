//
//  tsp_heuristic.h
//  stanford
//
//  Created by Murat Karaca on 12/7/24.
//

#include <fstream>

struct City {
    double x;
    double y;
};

int tsp_heuristic(std::ifstream& file);
