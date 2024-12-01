//
//  bellman_ford.h
//  stanford
//
//  Created by Murat Karaca on 12/1/24.
//

#include <fstream>

struct BellmanEdge {
    int u;
    int v;
    int weight;
};

int bellman_ford(std::ifstream& file);
