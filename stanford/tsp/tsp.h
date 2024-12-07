//
//  tsp.h
//  stanford
//
//  Created by Murat Karaca on 12/6/24.
//

#include <fstream>

struct Point {
    float x;
    float y;
};

int tsp(std::ifstream& file);
int tsp2(std::ifstream& file);
