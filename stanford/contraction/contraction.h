//
//  contraction.h
//  stanford
//
//  Created by Murat Karaca on 11/13/24.
//

#include <vector>

struct Edge {
    int u;
    int w;
};

int contraction(std::vector<Edge>& adjacencyList, int vertexCount);
