//
//  floyd_warshall.h
//  stanford
//
//  Created by Murat Karaca on 12/1/24.
//

#include "fstream"

struct FloydEdge {
    int u;
    int v;
    int weight;
};

int floyd_warshall(std::ifstream& file);
